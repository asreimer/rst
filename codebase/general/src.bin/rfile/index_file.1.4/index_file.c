/* index_file.c
   ============
   Author: R.J.Barnes
*/

/*
 LICENSE AND DISCLAIMER
 
 Copyright (c) 2012 The Johns Hopkins University/Applied Physics Laboratory
 
 This file is part of the Radar Software Toolkit (RST).
 
 RST is free software: you can redistribute it and/or modify
 it under the terms of the GNU Lesser General Public License as published by
 the Free Software Foundation, either version 3 of the License, or
 any later version.
 
 RST is distributed in the hope that it will be useful,
 but WITHOUT ANY WARRANTY; without even the implied warranty of
 MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 GNU Lesser General Public License for more details.
 
 You should have received a copy of the GNU Lesser General Public License
 along with RST.  If not, see <http://www.gnu.org/licenses/>.
 
 
 
*/

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include "rtypes.h"
#include "rtime.h"
#include "rfile.h"
#include "option.h"
#include "hlpstr.h"




struct OptionData opt;

int main(int argc,char *argv[]) {
  int ptr;
  int arg;
  FILE *fp;
  int yr,mo,dy,hr,mt; 
  double sc;
  double tme[2];
  void *tptr[2];
  unsigned char help=0;
  unsigned char option=0;

 

  OptionAdd(&opt,"-help",'x',&help);
  OptionAdd(&opt,"-option",'x',&option);

  arg=OptionProcess(1,argc,argv,&opt,NULL);   

 
  if (help==1) {
    OptionPrintInfo(stdout,hlpstr);
    exit(0);
  }
  
  if (option==1) {
    OptionDump(stdout,&opt);
    exit(0);
  }



  if (arg<argc) {
    fp=fopen(argv[arg],"r");
    if (fp==NULL) {
      fprintf(stderr,"File not found.\n");
      exit(-1);
    }
  } else fp=stdin;
  
  tptr[0]=tme;

  ptr=ftell(fp);

  while (RfileRead(fp,0,NULL,tptr) !=-1) {
    TimeEpochToYMDHMS(tme[0],&yr,&mo,&dy,&hr,&mt,&sc);
    fprintf(stdout,"%.4d %.2d %.2d %.2d %.2d %g ",yr,mo,dy,hr,mt,sc);
    TimeEpochToYMDHMS(tme[1],&yr,&mo,&dy,&hr,&mt,&sc);
    fprintf(stdout,"%.4d %.2d %.2d %.2d %.2d %g ",yr,mo,dy,hr,mt,sc);
    fprintf(stdout,"%d\n",ptr);
    ptr=ftell(fp);
  }
  if (arg<argc) fclose(fp);
  return 0;

}
  





