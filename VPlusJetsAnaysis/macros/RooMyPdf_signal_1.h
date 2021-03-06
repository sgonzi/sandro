/*****************************************************************************
 * Project: RooFit                                                           *
 *                                                                           *
  * This code was autogenerated by RooClassFactory                            * 
 *****************************************************************************/

#ifndef ROOMYPDF_SIGNAL_1
#define ROOMYPDF_SIGNAL_1

#include "RooAbsPdf.h"
#include "RooRealProxy.h"
#include "RooCategoryProxy.h"
#include "RooAbsReal.h"
#include "RooAbsCategory.h"
 
class RooMyPdf_signal_1 : public RooAbsPdf {
public:
  RooMyPdf_signal_1() {} ; 
  RooMyPdf_signal_1(const char *name, const char *title,
	      RooAbsReal& _y,
	      RooAbsReal& _alpha,
	      RooAbsReal& _beta,
	      RooAbsReal& _gamma);
  RooMyPdf_signal_1(const RooMyPdf_signal_1& other, const char* name=0) ;
  virtual TObject* clone(const char* newname) const { return new RooMyPdf_signal_1(*this,newname); }
  inline virtual ~RooMyPdf_signal_1() { }

protected:

  RooRealProxy y ;
  RooRealProxy alpha ;
  RooRealProxy beta ;
  RooRealProxy gamma ;
  
  Double_t evaluate() const ;

private:

  ClassDef(RooMyPdf_signal_1,1) // Your description goes here...
};
 
#endif
