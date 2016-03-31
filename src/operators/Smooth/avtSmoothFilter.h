/*****************************************************************************
*
* Copyright (c) 2000 - 2016, Lawrence Livermore National Security, LLC
* Produced at the Lawrence Livermore National Laboratory
* LLNL-CODE-442911
* All rights reserved.
*
* This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
* full copyright notice is contained in the file COPYRIGHT located at the root
* of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
*
* Redistribution  and  use  in  source  and  binary  forms,  with  or  without
* modification, are permitted provided that the following conditions are met:
*
*  - Redistributions of  source code must  retain the above  copyright notice,
*    this list of conditions and the disclaimer below.
*  - Redistributions in binary form must reproduce the above copyright notice,
*    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
*    documentation and/or other materials provided with the distribution.
*  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
*    be used to endorse or promote products derived from this software without
*    specific prior written permission.
*
* THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
* AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
* IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
* ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
* LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
* DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
* DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
* SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
* CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
* LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
* OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
* DAMAGE.
*
*****************************************************************************/

// ************************************************************************* //
//  File: avtSmoothFilter.h
// ************************************************************************* //

#ifndef AVT_Smooth_FILTER_H
#define AVT_Smooth_FILTER_H

#include <avtPluginDataTreeIterator.h>

#include <SmoothOperatorAttributes.h>

class vtkDataSet;


// ****************************************************************************
//  Class: avtSmoothFilter
//
//  Purpose:
//      A plugin operator for Smooth.
//
//  Programmer: childs -- generated by xml2avt
//  Creation:   Sun Aug 14 11:59:58 PDT 2005
//
//  Modifications:
//    Jeremy Meredith, Fri Apr 30 16:54:29 EDT 2010
//    Removed warning for non-polydata -- just try to fix it instead.
//
//    Eric Brugger, Thu Aug 14 16:39:28 PDT 2014
//    Modified the class to work with avtDataRepresentation.
//
// ****************************************************************************

class avtSmoothFilter : public avtPluginDataTreeIterator
{
  public:
                         avtSmoothFilter();
    virtual             ~avtSmoothFilter();

    static avtFilter    *Create();

    virtual const char  *GetType(void)  { return "avtSmoothFilter"; };
    virtual const char  *GetDescription(void)
                             { return "Smooth"; };

    virtual void         SetAtts(const AttributeGroup*);
    virtual bool         Equivalent(const AttributeGroup*);

  protected:
    SmoothOperatorAttributes   atts;

    virtual avtDataRepresentation *ExecuteData(avtDataRepresentation *);
    virtual void          PreExecute(void);
    virtual void          UpdateDataObjectInfo(void);
};


#endif
