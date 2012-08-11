/**
***  Copyright (c) 1995, 1996, 1997, 1998, 1999, 2000 by
***  The Board of Trustees of the University of Illinois.
***  All rights reserved.
**/

#ifndef OPT_PME_H
#define OPT_PME_H

#include "ComputeHomePatches.h"
#include "PmeBase.h"
#include "NamdTypes.h"
#include "SimParameters.h"

class OptPmeRealSpace;
//class ComputeMgr;
class SubmitReduction;
class OptPmeGridMsg;
class OptPmeMgr;

#include "OptPmeMgr.decl.h"
#include "OptPmeRealSpace.h"

struct PencilElement{
  bool     isActive;
  int      xmin, xmax;  
  int      ymin, ymax;  
  int      zmin, zmax;
  int      ib, jb;
  double   * data;
};

struct PatchGridElem {
  int              xstart, xlen;
  int              ystart, ylen;
  int              zstart, zlen;  
  int              patchID;
  float          * data;
};


class OptPmeCompute : public ComputeHomePatches {
public:
  OptPmeCompute(ComputeID c);
  virtual ~OptPmeCompute();
  void doWork();
  void sendPencils();
  void copyPencils(OptPmeGridMsg *);
  void ungridForces();
  void setMgr(OptPmeMgr *mgr) { myMgr = mgr; }

  double  *zline_storage;   //Make it private later
  float   *sp_zstorage;
 private:
  PmeGrid myGrid;
  int qsize, fsize;
  //normalized patch corrdinates
  int xstart, xlen, ystart, ylen, zstart, zlen;
  int alchFepOn, alchThermIntOn, lesOn, pairOn;
  
  double **q_arr;
  int nzlines;
  PmeReduction evir;
  SubmitReduction *reduction;
  SubmitReduction *amd_reduction;
  int strayChargeErrors;
  int numLocalAtoms;
  PmeParticle  * localData;
  unsigned char * localPartition;
  OptPmeRealSpace * myRealSpace;
  OptPmeMgr * myMgr;

  ResizeArray <PencilElement>   pencilVec;

  bool _initialized;
  void initializeOptPmeCompute();
  void resetPatchCoordinates (const Lattice &lattice);
};


#endif

