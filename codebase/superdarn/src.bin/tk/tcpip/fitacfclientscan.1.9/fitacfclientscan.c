/* fitacfclientscan.c
   ============--====
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
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <unistd.h>
#include <zlib.h>
#include "rtypes.h"
#include "option.h"
#include "connex.h"
#include "dmap.h"
#include "rprm.h"
#include "fitdata.h"
#include "scandata.h"
#include "downloadscan.h"
#include "errstr.h"
#include "hlpstr.h"




struct RadarScan *rec;

struct OptionData opt;

int main(int argc,char *argv[]) {
  int arg;
  unsigned char help=0;
  unsigned char option=0;


  int sock;
  int remote_port=0;
  char host[256];
  struct RadarParm *prm;
  struct FitData *fit;
  

  prm=RadarParmMake();
  fit=FitMake();
  rec=RadarScanMake();

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


  if (argc-arg<2) {
    OptionPrintInfo(stdout,errstr);
    exit(-1);
  }
   
 
  prm->scan=0;
 
  strcpy(host,argv[argc-2]);
  remote_port=atoi(argv[argc-1]);

  sock=ConnexOpen(host,remote_port,NULL); 
  if (sock<0) {
    fprintf(stderr,"Could not connect to host.\n");
    exit(-1);
  }

  do {
    downloadscan(sock,prm,fit,rec); 
  } while(1);

  return 0;
}
   

 










