// ***************************************************************************
//
// Copyright (c) 2000 - 2018, Lawrence Livermore National Security, LLC
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

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: BoxAttributes
//
// Purpose:
//    This class contains attributes for the box operator.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class BoxAttributes extends AttributeSubject implements Plugin
{
    private static int BoxAttributes_numAdditionalAtts = 8;

    // Enum values
    public final static int AMOUNT_SOME = 0;
    public final static int AMOUNT_ALL = 1;


    public BoxAttributes()
    {
        super(BoxAttributes_numAdditionalAtts);

        amount = AMOUNT_SOME;
        minx = 0;
        maxx = 1;
        miny = 0;
        maxy = 1;
        minz = 0;
        maxz = 1;
        inverse = false;
    }

    public BoxAttributes(int nMoreFields)
    {
        super(BoxAttributes_numAdditionalAtts + nMoreFields);

        amount = AMOUNT_SOME;
        minx = 0;
        maxx = 1;
        miny = 0;
        maxy = 1;
        minz = 0;
        maxz = 1;
        inverse = false;
    }

    public BoxAttributes(BoxAttributes obj)
    {
        super(obj);

        amount = obj.amount;
        minx = obj.minx;
        maxx = obj.maxx;
        miny = obj.miny;
        maxy = obj.maxy;
        minz = obj.minz;
        maxz = obj.maxz;
        inverse = obj.inverse;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return BoxAttributes_numAdditionalAtts;
    }

    public boolean equals(BoxAttributes obj)
    {
        // Create the return value
        return ((amount == obj.amount) &&
                (minx == obj.minx) &&
                (maxx == obj.maxx) &&
                (miny == obj.miny) &&
                (maxy == obj.maxy) &&
                (minz == obj.minz) &&
                (maxz == obj.maxz) &&
                (inverse == obj.inverse));
    }

    public String GetName() { return "Box"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetAmount(int amount_)
    {
        amount = amount_;
        Select(0);
    }

    public void SetMinx(double minx_)
    {
        minx = minx_;
        Select(1);
    }

    public void SetMaxx(double maxx_)
    {
        maxx = maxx_;
        Select(2);
    }

    public void SetMiny(double miny_)
    {
        miny = miny_;
        Select(3);
    }

    public void SetMaxy(double maxy_)
    {
        maxy = maxy_;
        Select(4);
    }

    public void SetMinz(double minz_)
    {
        minz = minz_;
        Select(5);
    }

    public void SetMaxz(double maxz_)
    {
        maxz = maxz_;
        Select(6);
    }

    public void SetInverse(boolean inverse_)
    {
        inverse = inverse_;
        Select(7);
    }

    // Property getting methods
    public int     GetAmount() { return amount; }
    public double  GetMinx() { return minx; }
    public double  GetMaxx() { return maxx; }
    public double  GetMiny() { return miny; }
    public double  GetMaxy() { return maxy; }
    public double  GetMinz() { return minz; }
    public double  GetMaxz() { return maxz; }
    public boolean GetInverse() { return inverse; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteInt(amount);
        if(WriteSelect(1, buf))
            buf.WriteDouble(minx);
        if(WriteSelect(2, buf))
            buf.WriteDouble(maxx);
        if(WriteSelect(3, buf))
            buf.WriteDouble(miny);
        if(WriteSelect(4, buf))
            buf.WriteDouble(maxy);
        if(WriteSelect(5, buf))
            buf.WriteDouble(minz);
        if(WriteSelect(6, buf))
            buf.WriteDouble(maxz);
        if(WriteSelect(7, buf))
            buf.WriteBool(inverse);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetAmount(buf.ReadInt());
            break;
        case 1:
            SetMinx(buf.ReadDouble());
            break;
        case 2:
            SetMaxx(buf.ReadDouble());
            break;
        case 3:
            SetMiny(buf.ReadDouble());
            break;
        case 4:
            SetMaxy(buf.ReadDouble());
            break;
        case 5:
            SetMinz(buf.ReadDouble());
            break;
        case 6:
            SetMaxz(buf.ReadDouble());
            break;
        case 7:
            SetInverse(buf.ReadBool());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + indent + "amount = ";
        if(amount == AMOUNT_SOME)
            str = str + "AMOUNT_SOME";
        if(amount == AMOUNT_ALL)
            str = str + "AMOUNT_ALL";
        str = str + "\n";
        str = str + doubleToString("minx", minx, indent) + "\n";
        str = str + doubleToString("maxx", maxx, indent) + "\n";
        str = str + doubleToString("miny", miny, indent) + "\n";
        str = str + doubleToString("maxy", maxy, indent) + "\n";
        str = str + doubleToString("minz", minz, indent) + "\n";
        str = str + doubleToString("maxz", maxz, indent) + "\n";
        str = str + boolToString("inverse", inverse, indent) + "\n";
        return str;
    }


    // Attributes
    private int     amount;
    private double  minx;
    private double  maxx;
    private double  miny;
    private double  maxy;
    private double  minz;
    private double  maxz;
    private boolean inverse;
}

