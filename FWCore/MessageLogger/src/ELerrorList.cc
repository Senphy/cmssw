// ----------------------------------------------------------------------
//
// ELerrorList.cc
//
//
// 9/21/00 	mf	Created
// 10/4/00	mf	excludeModule()
//			intializer for moduleOfINterest in constructors
//  4/4/01	mf	Simplify filter/exclude logic by using base class 
//			method thisShouldBeIgnored().  Eliminate 
//			moduleOfinterest and moduleToexclude.
//
// ----------------------------------------------------------------------


#include "FWCore/MessageLogger/interface/ELerrorList.h"

#ifdef NOTNEEDED
#ifndef IOSTREAM_INCLUDED
#endif
#endif

#ifndef FSTREAM_INCLUDED
#endif


#ifndef ELSTRING_H
  #include "FWCore/MessageLogger/interface/ELstring.h"
#endif

#ifndef ELADMINISTRATOR_H
  #include "FWCore/MessageLogger/interface/ELadministrator.h"
#endif

#include "FWCore/MessageLogger/interface/ELcontextSupplier.h"

// Possible Traces:
// #define ELerrorListCONSTRUCTOR_TRACE
// #define ELerrorListTRACE_LOG

namespace edm {       


// ----------------------------------------------------------------------
// Constructors:
// ----------------------------------------------------------------------

ELerrorList::ELerrorList(std::list<ErrorObj> & errorList) : 
		ELdestination (), 
		errorObjs ( errorList )
{

  #ifdef ELerrorListCONSTRUCTOR_TRACE
    std::cerr << "Constructor for ELerrorList()\n";
  #endif

}  // ELerrorList()

ELerrorList::ELerrorList(const ELerrorList & orig) :
		ELdestination (), 
		errorObjs ( orig.errorObjs )
{

  #ifdef ELerrorListCONSTRUCTOR_TRACE
    std::cerr << "Copy Constructor for ELerrorList()\n";
  #endif

  ignoreMostModules    = orig.ignoreMostModules;
  respondToThese       = orig.respondToThese;
  respondToMostModules = orig.respondToMostModules;
  ignoreThese          = orig.ignoreThese;

}  // ELerrorList()


ELerrorList::~ELerrorList()  {

  #ifdef ELerrorListCONSTRUCTOR_TRACE
    std::cerr << "Destructor for ELerrorList\n";
  #endif

}  // ~ELerrorList()


// ----------------------------------------------------------------------
// Methods invoked by the ELadministrator:
// ----------------------------------------------------------------------

ELerrorList *
ELerrorList::clone() const  {

  return new ELerrorList( *this );

} // clone()


bool ELerrorList::log( const ErrorObj & msg )  {

  #ifdef ELerrorListTRACE_LOG
    std::cerr << "    =:=:=: Log to an ELerrorList \n";
  #endif

  ErrorObj m (msg);

  // See if this message is to be acted upon, and add it to limits table
  // if it was not already present:
  //
  if ( msg.xid().severity < threshold )        return false;
  if ( thisShouldBeIgnored(msg.xid().module) ) return false;
  if ( ! limits.add( msg.xid() )      )        return false;

  #ifdef ELerrorListTRACE_LOG
    std::cerr << "    =:=:=: Limits table work done \n";
  #endif

  // add a last item to the message:  The fullContext string supplied.

  m.emit(ELadministrator::instance()->getContextSupplier().fullContext());

  // Now just put m on the list:

  errorObjs.push_back(m);

  // Done; message has been fully processed:
  //

  #ifdef ELerrorListTRACE_LOG
    std::cerr << "  =:=:=: log(msg) done: \n";
  #endif

  return true;

}  // log()


// Remainder are from base class.


// ----------------------------------------------------------------------
// errorList methods:
// ----------------------------------------------------------------------


// ----------------------------------------------------------------------

} // end of namespace edm  */
