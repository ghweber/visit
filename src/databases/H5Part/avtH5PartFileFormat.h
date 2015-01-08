/*****************************************************************************
*
* Copyright (c) 2000 - 2015, Lawrence Livermore National Security, LLC
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
//                            avtH5PartFileFormat.h                          //
// ************************************************************************* //

#ifndef AVT_H5Part_FILE_FORMAT_H
#define AVT_H5Part_FILE_FORMAT_H

#include <visit-config.h>

#include <avtMTSDFileFormat.h>

// H5Part
#include <H5Part.h>
#include <H5Block.h>
#include <H5BlockTypes.h>

// STL
#include <vector>
#include <map>
#include <string>

#ifdef HAVE_LIBFASTBIT
#include "hdf5_fastquery.h"
#include "HistogramCache.h"

#include <fastbit-config.h>
#if FASTBIT_IBIS_INT_VERSION < 1020000
#error "The H5Part plugin requires FastBit 1.2.0 or newer."
#endif

#endif

class DBOptionsAttributes;

#ifdef HAVE_LIBFASTBIT
class avtIdentifierSelection;
class avtHistogramSpecification;
#endif


// ****************************************************************************
//  Class: avtH5PartFileFormat
//
//  Purpose:
//      Reads in H5Part files as a plugin to VisIt.
//
//  Programmer: ghweber -- generated by xml2avt
//  Creation:   Tue Feb 9 13:44:50 PST 2010
//
//  Modifications:
//    Kurt Stockinger, Tue Aug 28 17:35:50 PDT 2007
//    Added support for field data
//
//    Gunther H. Weber, Fri Apr 17 13:03:47 PDT 2009
//    Added option to reject file if FastBit index is present.
//
//    Gunther H. Weber, Tue Nov 10 19:48:28 PST 2009
//    Removed unused data members.
//
//    Gunther H. Weber, Tue Feb  9 17:16:20 PST 2010
//    Complete restructuring. Recreated plugin as MTSD that supports
//    domain decomposition and rewrote major portions using original
//    pieces. Merged with HDF_UC plugin.
//
// ****************************************************************************

class avtH5PartFileFormat : public avtMTSDFileFormat
{
  public:
                       avtH5PartFileFormat(const char *, DBOptionsAttributes *);
    virtual           ~avtH5PartFileFormat();

#ifdef HAVE_LIBFASTBIT
    //
    // This is used to return unconvention data -- ranging from material
    // information to information about block connectivity.
    //
    virtual void      *GetAuxiliaryData(const char *var, int timestep, 
                                        const char *type, void *args, 
                                        DestructorFunction &);
#endif
    //
    // If you know the times and cycle numbers, overload this function.
    // Otherwise, VisIt will make up some reasonable ones for you.
    //
    // virtual void        GetCycles(std::vector<int> &);
    // virtual void        GetTimes(std::vector<double> &);
    //

    virtual int            GetNTimesteps(void);

    virtual const char    *GetType(void)   { return "H5Part"; };
    virtual void           FreeUpResources(void); 

#ifdef HAVE_LIBFASTBIT 
    virtual bool           CanCacheVariable(const char *) { return !useFastBitIndex; /* FIXME: Field variables can be cached */ };
    virtual void           RegisterDataSelections(const std::vector<avtDataSelection_p>&,
                               std::vector<bool> *);
#endif

    virtual vtkDataSet    *GetMesh(int, const char *);
    virtual vtkDataArray  *GetVar(int, const char *);
    virtual vtkDataArray  *GetVectorVar(int, const char *);

    virtual void           ActivateTimestep(int ts);

  protected:
    // DATA MEMBERS
    // ... Constants
    static const int       maxVarNameLen = 256; // Maximum variable name length used in H5Part calls

    // ... Reader options
    bool                   useFastBitIndex;
    bool                   disableDomainDecomposition;
    // ... File information
    H5PartFile            *file;
    enum { cartesianCoordSystem, cylindricalCoordSystem, sphericalCoordSystem }
                           coordType;
    int                    particleNSpatialDims;
    typedef std::map<std::string, h5part_int64_t>
                           VarNameToInt64Map_t;
    VarNameToInt64Map_t    particleVarNameToTypeMap;
    VarNameToInt64Map_t    fieldScalarVarNameToTypeMap;
    VarNameToInt64Map_t    fieldVectorVarNameToTypeMap;
    VarNameToInt64Map_t    fieldVectorVarNameToFieldRankMap;
    h5part_int64_t         numTimestepsInFile;
    h5part_int64_t         activeTimeStep;

    virtual void           PopulateDatabaseMetaData(avtDatabaseMetaData *, int);

  private:
    void                   SelectParticlesToRead();
    vtkDataSet            *GetParticleMesh(int);
    vtkDataSet            *GetFieldMesh(int, const char *);
    vtkDataArray          *GetFieldVar(int, const char*);
    void                   GetSubBlock(h5part_int64_t gridDims[3], h5part_int64_t subBlockDims[6]);
    std::string            DoubleToString(double x);
#ifdef HAVE_LIBFASTBIT
    void                   ConstructHistogram(avtHistogramSpecification *spec);

    avtIdentifierSelection
                          *ConstructIdentifiersFromDataRangeSelection(
                                  std::vector<avtDataSelection *> &);
    void                   ConstructIdQueryString(const std::vector<double>&,
                                  const std::string &, std::string& );
    void                   PerformQuery();
    
    // Is there an active query? If value is stringQuery, "queryString" contains
    // the current query that needs to be run to get the data selection (queryResults).
    // If value is idListQuery, "queryIdList" contains a list of particle ids (likely
    // from a named selection).
    enum { noQuery = 0, stringQuery, idListQuery }
                           querySpecified;
    // Are the query results (queryResults) valid? This variable is set to false
    // by RegisterDataSelection to indicate that there is a new queryString or
    // queryIdList and that PerformQuery needs to be called to update queryResults
    bool                   queryResultsValid;
    // Is there an active data selection, i.e., does queryResults contain a valid
    // list of particles indices to load for an active query?
    bool                   dataSelectionActive;
    // The name of the variable which contains the particle id
    std::string            idVariableName;
    // String of a possible active stringQuery
    std::string            queryString;
    // List of ids (values if "idVariableName") for a named selection query
    std::vector<double>    queryIdList;
    // Result from a current query
    std::vector<hsize_t>   queryResults;
    // The HDF5_FastQuery reader. Used mainly to read index information from file.
    HDF5_FQ                reader;
    // Histogram cache for already computed histograms
    HistogramCache         histoCache;
#endif
};

#endif
