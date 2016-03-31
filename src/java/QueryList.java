// ***************************************************************************
//
// Copyright (c) 2000 - 2016, Lawrence Livermore National Security, LLC
// Produced at the Lawrence Livermore National Laboratory
// LLNL-CODE-442911
// All rights reserved.
//
// This file is  part of VisIt. For  details, see https://visit.llnl.gov/.  The
// full copyright notice is contained in the file COPYRIGHT located at the root
// of the VisIt distribution or at http://www.llnl.gov/visit/copyright.html.
//
// Redistribution  and  use  in  source  and  binary  forms,  with  or  without
// modification, are permitted provided that the following conditions are met:
//
//  - Redistributions of  source code must  retain the above  copyright notice,
//    this list of conditions and the disclaimer below.
//  - Redistributions in binary form must reproduce the above copyright notice,
//    this  list of  conditions  and  the  disclaimer (as noted below)  in  the
//    documentation and/or other materials provided with the distribution.
//  - Neither the name of  the LLNS/LLNL nor the names of  its contributors may
//    be used to endorse or promote products derived from this software without
//    specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT  HOLDERS AND CONTRIBUTORS "AS IS"
// AND ANY EXPRESS OR  IMPLIED WARRANTIES, INCLUDING,  BUT NOT  LIMITED TO, THE
// IMPLIED WARRANTIES OF MERCHANTABILITY AND  FITNESS FOR A PARTICULAR  PURPOSE
// ARE  DISCLAIMED. IN  NO EVENT  SHALL LAWRENCE  LIVERMORE NATIONAL  SECURITY,
// LLC, THE  U.S.  DEPARTMENT OF  ENERGY  OR  CONTRIBUTORS BE  LIABLE  FOR  ANY
// DIRECT,  INDIRECT,   INCIDENTAL,   SPECIAL,   EXEMPLARY,  OR   CONSEQUENTIAL
// DAMAGES (INCLUDING, BUT NOT  LIMITED TO, PROCUREMENT OF  SUBSTITUTE GOODS OR
// SERVICES; LOSS OF  USE, DATA, OR PROFITS; OR  BUSINESS INTERRUPTION) HOWEVER
// CAUSED  AND  ON  ANY  THEORY  OF  LIABILITY,  WHETHER  IN  CONTRACT,  STRICT
// LIABILITY, OR TORT  (INCLUDING NEGLIGENCE OR OTHERWISE)  ARISING IN ANY  WAY
// OUT OF THE  USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.
//
// ***************************************************************************

package llnl.visit;

import java.util.Vector;
import java.lang.Integer;

// ****************************************************************************
// Class: QueryList
//
// Purpose:
//    List of supported queries
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class QueryList extends AttributeSubject
{
    private static int QueryList_numAdditionalAtts = 10;

    // Enum values
    public final static int QUERYTYPE_DATABASEQUERY = 0;
    public final static int QUERYTYPE_POINTQUERY = 1;
    public final static int QUERYTYPE_LINEQUERY = 2;

    public final static int WINDOWTYPE_BASIC = 0;
    public final static int WINDOWTYPE_DOMAINNODE = 1;
    public final static int WINDOWTYPE_DOMAINNODEVARS = 2;
    public final static int WINDOWTYPE_DOMAINZONE = 3;
    public final static int WINDOWTYPE_DOMAINZONEVARS = 4;
    public final static int WINDOWTYPE_ACTUALDATA = 5;
    public final static int WINDOWTYPE_ACTUALDATAVARS = 6;
    public final static int WINDOWTYPE_LINEDISTRIBUTION = 7;
    public final static int WINDOWTYPE_HOHLRAUMFLUX = 8;
    public final static int WINDOWTYPE_CONNCOMPSUMMARY = 9;
    public final static int WINDOWTYPE_SHAPELETSDECOMP = 10;
    public final static int WINDOWTYPE_XRAYIMAGE = 11;
    public final static int WINDOWTYPE_LINESAMPLERINFO = 12;
    public final static int WINDOWTYPE_STREAMLINEINFO = 13;
    public final static int WINDOWTYPE_PICK = 14;
    public final static int WINDOWTYPE_LINEOUT = 15;
    public final static int WINDOWTYPE_COMPACTNESS = 16;

    public final static int GROUPS_CURVERELATED = 0;
    public final static int GROUPS_MESHRELATED = 1;
    public final static int GROUPS_TIMERELATED = 2;
    public final static int GROUPS_VARIABLERELATED = 3;
    public final static int GROUPS_SHAPERELATED = 4;
    public final static int GROUPS_CONNECTEDCOMPONENTSRELATED = 5;
    public final static int GROUPS_MISCELLANEOUS = 6;
    public final static int GROUPS_NUMGROUPS = 7;

    public final static int QUERYMODE_QUERYONLY = 0;
    public final static int QUERYMODE_QUERYANDTIME = 1;
    public final static int QUERYMODE_TIMEONLY = 2;


    public QueryList()
    {
        super(QueryList_numAdditionalAtts);

        names = new Vector();
        types = new Vector();
        groups = new Vector();
        numInputs = new Vector();
        allowedVarTypes = new Vector();
        winType = new Vector();
        queryMode = new Vector();
        numVars = new Vector();
        canBePublic = new Vector();
        requiresVarSelection = new Vector();
    }

    public QueryList(int nMoreFields)
    {
        super(QueryList_numAdditionalAtts + nMoreFields);

        names = new Vector();
        types = new Vector();
        groups = new Vector();
        numInputs = new Vector();
        allowedVarTypes = new Vector();
        winType = new Vector();
        queryMode = new Vector();
        numVars = new Vector();
        canBePublic = new Vector();
        requiresVarSelection = new Vector();
    }

    public QueryList(QueryList obj)
    {
        super(QueryList_numAdditionalAtts);

        int i;

        names = new Vector(obj.names.size());
        for(i = 0; i < obj.names.size(); ++i)
            names.addElement(new String((String)obj.names.elementAt(i)));

        types = new Vector();
        for(i = 0; i < obj.types.size(); ++i)
        {
            Integer iv = (Integer)obj.types.elementAt(i);
            types.addElement(new Integer(iv.intValue()));
        }
        groups = new Vector();
        for(i = 0; i < obj.groups.size(); ++i)
        {
            Integer iv = (Integer)obj.groups.elementAt(i);
            groups.addElement(new Integer(iv.intValue()));
        }
        numInputs = new Vector();
        for(i = 0; i < obj.numInputs.size(); ++i)
        {
            Integer iv = (Integer)obj.numInputs.elementAt(i);
            numInputs.addElement(new Integer(iv.intValue()));
        }
        allowedVarTypes = new Vector();
        for(i = 0; i < obj.allowedVarTypes.size(); ++i)
        {
            Integer iv = (Integer)obj.allowedVarTypes.elementAt(i);
            allowedVarTypes.addElement(new Integer(iv.intValue()));
        }
        winType = new Vector();
        for(i = 0; i < obj.winType.size(); ++i)
        {
            Integer iv = (Integer)obj.winType.elementAt(i);
            winType.addElement(new Integer(iv.intValue()));
        }
        queryMode = new Vector();
        for(i = 0; i < obj.queryMode.size(); ++i)
        {
            Integer iv = (Integer)obj.queryMode.elementAt(i);
            queryMode.addElement(new Integer(iv.intValue()));
        }
        numVars = new Vector();
        for(i = 0; i < obj.numVars.size(); ++i)
        {
            Integer iv = (Integer)obj.numVars.elementAt(i);
            numVars.addElement(new Integer(iv.intValue()));
        }
        canBePublic = new Vector();
        for(i = 0; i < obj.canBePublic.size(); ++i)
        {
            Integer iv = (Integer)obj.canBePublic.elementAt(i);
            canBePublic.addElement(new Integer(iv.intValue()));
        }
        requiresVarSelection = new Vector();
        for(i = 0; i < obj.requiresVarSelection.size(); ++i)
        {
            Integer iv = (Integer)obj.requiresVarSelection.elementAt(i);
            requiresVarSelection.addElement(new Integer(iv.intValue()));
        }

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return QueryList_numAdditionalAtts;
    }

    public boolean equals(QueryList obj)
    {
        int i;

        // Compare the elements in the names vector.
        boolean names_equal = (obj.names.size() == names.size());
        for(i = 0; (i < names.size()) && names_equal; ++i)
        {
            // Make references to String from Object.
            String names1 = (String)names.elementAt(i);
            String names2 = (String)obj.names.elementAt(i);
            names_equal = names1.equals(names2);
        }
        // Compare the elements in the types vector.
        boolean types_equal = (obj.types.size() == types.size());
        for(i = 0; (i < types.size()) && types_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer types1 = (Integer)types.elementAt(i);
            Integer types2 = (Integer)obj.types.elementAt(i);
            types_equal = types1.equals(types2);
        }
        // Compare the elements in the groups vector.
        boolean groups_equal = (obj.groups.size() == groups.size());
        for(i = 0; (i < groups.size()) && groups_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer groups1 = (Integer)groups.elementAt(i);
            Integer groups2 = (Integer)obj.groups.elementAt(i);
            groups_equal = groups1.equals(groups2);
        }
        // Compare the elements in the numInputs vector.
        boolean numInputs_equal = (obj.numInputs.size() == numInputs.size());
        for(i = 0; (i < numInputs.size()) && numInputs_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer numInputs1 = (Integer)numInputs.elementAt(i);
            Integer numInputs2 = (Integer)obj.numInputs.elementAt(i);
            numInputs_equal = numInputs1.equals(numInputs2);
        }
        // Compare the elements in the allowedVarTypes vector.
        boolean allowedVarTypes_equal = (obj.allowedVarTypes.size() == allowedVarTypes.size());
        for(i = 0; (i < allowedVarTypes.size()) && allowedVarTypes_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer allowedVarTypes1 = (Integer)allowedVarTypes.elementAt(i);
            Integer allowedVarTypes2 = (Integer)obj.allowedVarTypes.elementAt(i);
            allowedVarTypes_equal = allowedVarTypes1.equals(allowedVarTypes2);
        }
        // Compare the elements in the winType vector.
        boolean winType_equal = (obj.winType.size() == winType.size());
        for(i = 0; (i < winType.size()) && winType_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer winType1 = (Integer)winType.elementAt(i);
            Integer winType2 = (Integer)obj.winType.elementAt(i);
            winType_equal = winType1.equals(winType2);
        }
        // Compare the elements in the queryMode vector.
        boolean queryMode_equal = (obj.queryMode.size() == queryMode.size());
        for(i = 0; (i < queryMode.size()) && queryMode_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer queryMode1 = (Integer)queryMode.elementAt(i);
            Integer queryMode2 = (Integer)obj.queryMode.elementAt(i);
            queryMode_equal = queryMode1.equals(queryMode2);
        }
        // Compare the elements in the numVars vector.
        boolean numVars_equal = (obj.numVars.size() == numVars.size());
        for(i = 0; (i < numVars.size()) && numVars_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer numVars1 = (Integer)numVars.elementAt(i);
            Integer numVars2 = (Integer)obj.numVars.elementAt(i);
            numVars_equal = numVars1.equals(numVars2);
        }
        // Compare the elements in the canBePublic vector.
        boolean canBePublic_equal = (obj.canBePublic.size() == canBePublic.size());
        for(i = 0; (i < canBePublic.size()) && canBePublic_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer canBePublic1 = (Integer)canBePublic.elementAt(i);
            Integer canBePublic2 = (Integer)obj.canBePublic.elementAt(i);
            canBePublic_equal = canBePublic1.equals(canBePublic2);
        }
        // Compare the elements in the requiresVarSelection vector.
        boolean requiresVarSelection_equal = (obj.requiresVarSelection.size() == requiresVarSelection.size());
        for(i = 0; (i < requiresVarSelection.size()) && requiresVarSelection_equal; ++i)
        {
            // Make references to Integer from Object.
            Integer requiresVarSelection1 = (Integer)requiresVarSelection.elementAt(i);
            Integer requiresVarSelection2 = (Integer)obj.requiresVarSelection.elementAt(i);
            requiresVarSelection_equal = requiresVarSelection1.equals(requiresVarSelection2);
        }
        // Create the return value
        return (names_equal &&
                types_equal &&
                groups_equal &&
                numInputs_equal &&
                allowedVarTypes_equal &&
                winType_equal &&
                queryMode_equal &&
                numVars_equal &&
                canBePublic_equal &&
                requiresVarSelection_equal);
    }

    // Property setting methods
    public void SetNames(Vector names_)
    {
        names = names_;
        Select(0);
    }

    public void SetTypes(Vector types_)
    {
        types = types_;
        Select(1);
    }

    public void SetGroups(Vector groups_)
    {
        groups = groups_;
        Select(2);
    }

    public void SetNumInputs(Vector numInputs_)
    {
        numInputs = numInputs_;
        Select(3);
    }

    public void SetAllowedVarTypes(Vector allowedVarTypes_)
    {
        allowedVarTypes = allowedVarTypes_;
        Select(4);
    }

    public void SetWinType(Vector winType_)
    {
        winType = winType_;
        Select(5);
    }

    public void SetQueryMode(Vector queryMode_)
    {
        queryMode = queryMode_;
        Select(6);
    }

    public void SetNumVars(Vector numVars_)
    {
        numVars = numVars_;
        Select(7);
    }

    public void SetCanBePublic(Vector canBePublic_)
    {
        canBePublic = canBePublic_;
        Select(8);
    }

    public void SetRequiresVarSelection(Vector requiresVarSelection_)
    {
        requiresVarSelection = requiresVarSelection_;
        Select(9);
    }

    // Property getting methods
    public Vector GetNames() { return names; }
    public Vector GetTypes() { return types; }
    public Vector GetGroups() { return groups; }
    public Vector GetNumInputs() { return numInputs; }
    public Vector GetAllowedVarTypes() { return allowedVarTypes; }
    public Vector GetWinType() { return winType; }
    public Vector GetQueryMode() { return queryMode; }
    public Vector GetNumVars() { return numVars; }
    public Vector GetCanBePublic() { return canBePublic; }
    public Vector GetRequiresVarSelection() { return requiresVarSelection; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteStringVector(names);
        if(WriteSelect(1, buf))
            buf.WriteIntVector(types);
        if(WriteSelect(2, buf))
            buf.WriteIntVector(groups);
        if(WriteSelect(3, buf))
            buf.WriteIntVector(numInputs);
        if(WriteSelect(4, buf))
            buf.WriteIntVector(allowedVarTypes);
        if(WriteSelect(5, buf))
            buf.WriteIntVector(winType);
        if(WriteSelect(6, buf))
            buf.WriteIntVector(queryMode);
        if(WriteSelect(7, buf))
            buf.WriteIntVector(numVars);
        if(WriteSelect(8, buf))
            buf.WriteIntVector(canBePublic);
        if(WriteSelect(9, buf))
            buf.WriteIntVector(requiresVarSelection);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetNames(buf.ReadStringVector());
            break;
        case 1:
            SetTypes(buf.ReadIntVector());
            break;
        case 2:
            SetGroups(buf.ReadIntVector());
            break;
        case 3:
            SetNumInputs(buf.ReadIntVector());
            break;
        case 4:
            SetAllowedVarTypes(buf.ReadIntVector());
            break;
        case 5:
            SetWinType(buf.ReadIntVector());
            break;
        case 6:
            SetQueryMode(buf.ReadIntVector());
            break;
        case 7:
            SetNumVars(buf.ReadIntVector());
            break;
        case 8:
            SetCanBePublic(buf.ReadIntVector());
            break;
        case 9:
            SetRequiresVarSelection(buf.ReadIntVector());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringVectorToString("names", names, indent) + "\n";
        str = str + intVectorToString("types", types, indent) + "\n";
        str = str + intVectorToString("groups", groups, indent) + "\n";
        str = str + intVectorToString("numInputs", numInputs, indent) + "\n";
        str = str + intVectorToString("allowedVarTypes", allowedVarTypes, indent) + "\n";
        str = str + intVectorToString("winType", winType, indent) + "\n";
        str = str + intVectorToString("queryMode", queryMode, indent) + "\n";
        str = str + intVectorToString("numVars", numVars, indent) + "\n";
        str = str + intVectorToString("canBePublic", canBePublic, indent) + "\n";
        str = str + intVectorToString("requiresVarSelection", requiresVarSelection, indent) + "\n";
        return str;
    }


    // Attributes
    private Vector names; // vector of String objects
    private Vector types; // vector of Integer objects
    private Vector groups; // vector of Integer objects
    private Vector numInputs; // vector of Integer objects
    private Vector allowedVarTypes; // vector of Integer objects
    private Vector winType; // vector of Integer objects
    private Vector queryMode; // vector of Integer objects
    private Vector numVars; // vector of Integer objects
    private Vector canBePublic; // vector of Integer objects
    private Vector requiresVarSelection; // vector of Integer objects
}

