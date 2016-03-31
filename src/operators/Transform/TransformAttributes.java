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

package llnl.visit.operators;

import llnl.visit.AttributeSubject;
import llnl.visit.CommunicationBuffer;
import llnl.visit.Plugin;

// ****************************************************************************
// Class: TransformAttributes
//
// Purpose:
//    This class contains attributes for the transform operator.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class TransformAttributes extends AttributeSubject implements Plugin
{
    private static int TransformAttributes_numAdditionalAtts = 37;

    // Enum values
    public final static int ANGLETYPE_DEG = 0;
    public final static int ANGLETYPE_RAD = 1;

    public final static int TRANSFORMTYPE_SIMILARITY = 0;
    public final static int TRANSFORMTYPE_COORDINATE = 1;
    public final static int TRANSFORMTYPE_LINEAR = 2;

    public final static int COORDINATESYSTEM_CARTESIAN = 0;
    public final static int COORDINATESYSTEM_CYLINDRICAL = 1;
    public final static int COORDINATESYSTEM_SPHERICAL = 2;

    public final static int VECTORTRANSFORMMETHOD_NONE = 0;
    public final static int VECTORTRANSFORMMETHOD_ASPOINT = 1;
    public final static int VECTORTRANSFORMMETHOD_ASDISPLACEMENT = 2;
    public final static int VECTORTRANSFORMMETHOD_ASDIRECTION = 3;


    public TransformAttributes()
    {
        super(TransformAttributes_numAdditionalAtts);

        doRotate = false;
        rotateOrigin = new double[3];
        rotateOrigin[0] = 0;
        rotateOrigin[1] = 0;
        rotateOrigin[2] = 0;
        rotateAxis = new double[3];
        rotateAxis[0] = 0;
        rotateAxis[1] = 0;
        rotateAxis[2] = 1;
        rotateAmount = 0;
        rotateType = ANGLETYPE_DEG;
        doScale = false;
        scaleOrigin = new double[3];
        scaleOrigin[0] = 0;
        scaleOrigin[1] = 0;
        scaleOrigin[2] = 0;
        scaleX = 1;
        scaleY = 1;
        scaleZ = 1;
        doTranslate = false;
        translateX = 0;
        translateY = 0;
        translateZ = 0;
        transformType = TRANSFORMTYPE_SIMILARITY;
        inputCoordSys = COORDINATESYSTEM_CARTESIAN;
        outputCoordSys = COORDINATESYSTEM_SPHERICAL;
        continuousPhi = false;
        m00 = 1;
        m01 = 0;
        m02 = 0;
        m03 = 0;
        m10 = 0;
        m11 = 1;
        m12 = 0;
        m13 = 0;
        m20 = 0;
        m21 = 0;
        m22 = 1;
        m23 = 0;
        m30 = 0;
        m31 = 0;
        m32 = 0;
        m33 = 1;
        invertLinearTransform = false;
        vectorTransformMethod = VECTORTRANSFORMMETHOD_ASDIRECTION;
        transformVectors = true;
    }

    public TransformAttributes(int nMoreFields)
    {
        super(TransformAttributes_numAdditionalAtts + nMoreFields);

        doRotate = false;
        rotateOrigin = new double[3];
        rotateOrigin[0] = 0;
        rotateOrigin[1] = 0;
        rotateOrigin[2] = 0;
        rotateAxis = new double[3];
        rotateAxis[0] = 0;
        rotateAxis[1] = 0;
        rotateAxis[2] = 1;
        rotateAmount = 0;
        rotateType = ANGLETYPE_DEG;
        doScale = false;
        scaleOrigin = new double[3];
        scaleOrigin[0] = 0;
        scaleOrigin[1] = 0;
        scaleOrigin[2] = 0;
        scaleX = 1;
        scaleY = 1;
        scaleZ = 1;
        doTranslate = false;
        translateX = 0;
        translateY = 0;
        translateZ = 0;
        transformType = TRANSFORMTYPE_SIMILARITY;
        inputCoordSys = COORDINATESYSTEM_CARTESIAN;
        outputCoordSys = COORDINATESYSTEM_SPHERICAL;
        continuousPhi = false;
        m00 = 1;
        m01 = 0;
        m02 = 0;
        m03 = 0;
        m10 = 0;
        m11 = 1;
        m12 = 0;
        m13 = 0;
        m20 = 0;
        m21 = 0;
        m22 = 1;
        m23 = 0;
        m30 = 0;
        m31 = 0;
        m32 = 0;
        m33 = 1;
        invertLinearTransform = false;
        vectorTransformMethod = VECTORTRANSFORMMETHOD_ASDIRECTION;
        transformVectors = true;
    }

    public TransformAttributes(TransformAttributes obj)
    {
        super(TransformAttributes_numAdditionalAtts);

        int i;

        doRotate = obj.doRotate;
        rotateOrigin = new double[3];
        rotateOrigin[0] = obj.rotateOrigin[0];
        rotateOrigin[1] = obj.rotateOrigin[1];
        rotateOrigin[2] = obj.rotateOrigin[2];

        rotateAxis = new double[3];
        rotateAxis[0] = obj.rotateAxis[0];
        rotateAxis[1] = obj.rotateAxis[1];
        rotateAxis[2] = obj.rotateAxis[2];

        rotateAmount = obj.rotateAmount;
        rotateType = obj.rotateType;
        doScale = obj.doScale;
        scaleOrigin = new double[3];
        scaleOrigin[0] = obj.scaleOrigin[0];
        scaleOrigin[1] = obj.scaleOrigin[1];
        scaleOrigin[2] = obj.scaleOrigin[2];

        scaleX = obj.scaleX;
        scaleY = obj.scaleY;
        scaleZ = obj.scaleZ;
        doTranslate = obj.doTranslate;
        translateX = obj.translateX;
        translateY = obj.translateY;
        translateZ = obj.translateZ;
        transformType = obj.transformType;
        inputCoordSys = obj.inputCoordSys;
        outputCoordSys = obj.outputCoordSys;
        continuousPhi = obj.continuousPhi;
        m00 = obj.m00;
        m01 = obj.m01;
        m02 = obj.m02;
        m03 = obj.m03;
        m10 = obj.m10;
        m11 = obj.m11;
        m12 = obj.m12;
        m13 = obj.m13;
        m20 = obj.m20;
        m21 = obj.m21;
        m22 = obj.m22;
        m23 = obj.m23;
        m30 = obj.m30;
        m31 = obj.m31;
        m32 = obj.m32;
        m33 = obj.m33;
        invertLinearTransform = obj.invertLinearTransform;
        vectorTransformMethod = obj.vectorTransformMethod;
        transformVectors = obj.transformVectors;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return TransformAttributes_numAdditionalAtts;
    }

    public boolean equals(TransformAttributes obj)
    {
        int i;

        // Compare the rotateOrigin arrays.
        boolean rotateOrigin_equal = true;
        for(i = 0; i < 3 && rotateOrigin_equal; ++i)
            rotateOrigin_equal = (rotateOrigin[i] == obj.rotateOrigin[i]);

        // Compare the rotateAxis arrays.
        boolean rotateAxis_equal = true;
        for(i = 0; i < 3 && rotateAxis_equal; ++i)
            rotateAxis_equal = (rotateAxis[i] == obj.rotateAxis[i]);

        // Compare the scaleOrigin arrays.
        boolean scaleOrigin_equal = true;
        for(i = 0; i < 3 && scaleOrigin_equal; ++i)
            scaleOrigin_equal = (scaleOrigin[i] == obj.scaleOrigin[i]);

        // Create the return value
        return ((doRotate == obj.doRotate) &&
                rotateOrigin_equal &&
                rotateAxis_equal &&
                (rotateAmount == obj.rotateAmount) &&
                (rotateType == obj.rotateType) &&
                (doScale == obj.doScale) &&
                scaleOrigin_equal &&
                (scaleX == obj.scaleX) &&
                (scaleY == obj.scaleY) &&
                (scaleZ == obj.scaleZ) &&
                (doTranslate == obj.doTranslate) &&
                (translateX == obj.translateX) &&
                (translateY == obj.translateY) &&
                (translateZ == obj.translateZ) &&
                (transformType == obj.transformType) &&
                (inputCoordSys == obj.inputCoordSys) &&
                (outputCoordSys == obj.outputCoordSys) &&
                (continuousPhi == obj.continuousPhi) &&
                (m00 == obj.m00) &&
                (m01 == obj.m01) &&
                (m02 == obj.m02) &&
                (m03 == obj.m03) &&
                (m10 == obj.m10) &&
                (m11 == obj.m11) &&
                (m12 == obj.m12) &&
                (m13 == obj.m13) &&
                (m20 == obj.m20) &&
                (m21 == obj.m21) &&
                (m22 == obj.m22) &&
                (m23 == obj.m23) &&
                (m30 == obj.m30) &&
                (m31 == obj.m31) &&
                (m32 == obj.m32) &&
                (m33 == obj.m33) &&
                (invertLinearTransform == obj.invertLinearTransform) &&
                (vectorTransformMethod == obj.vectorTransformMethod) &&
                (transformVectors == obj.transformVectors));
    }

    public String GetName() { return "Transform"; }
    public String GetVersion() { return "1.0"; }

    // Property setting methods
    public void SetDoRotate(boolean doRotate_)
    {
        doRotate = doRotate_;
        Select(0);
    }

    public void SetRotateOrigin(double[] rotateOrigin_)
    {
        rotateOrigin[0] = rotateOrigin_[0];
        rotateOrigin[1] = rotateOrigin_[1];
        rotateOrigin[2] = rotateOrigin_[2];
        Select(1);
    }

    public void SetRotateOrigin(double e0, double e1, double e2)
    {
        rotateOrigin[0] = e0;
        rotateOrigin[1] = e1;
        rotateOrigin[2] = e2;
        Select(1);
    }

    public void SetRotateAxis(double[] rotateAxis_)
    {
        rotateAxis[0] = rotateAxis_[0];
        rotateAxis[1] = rotateAxis_[1];
        rotateAxis[2] = rotateAxis_[2];
        Select(2);
    }

    public void SetRotateAxis(double e0, double e1, double e2)
    {
        rotateAxis[0] = e0;
        rotateAxis[1] = e1;
        rotateAxis[2] = e2;
        Select(2);
    }

    public void SetRotateAmount(double rotateAmount_)
    {
        rotateAmount = rotateAmount_;
        Select(3);
    }

    public void SetRotateType(int rotateType_)
    {
        rotateType = rotateType_;
        Select(4);
    }

    public void SetDoScale(boolean doScale_)
    {
        doScale = doScale_;
        Select(5);
    }

    public void SetScaleOrigin(double[] scaleOrigin_)
    {
        scaleOrigin[0] = scaleOrigin_[0];
        scaleOrigin[1] = scaleOrigin_[1];
        scaleOrigin[2] = scaleOrigin_[2];
        Select(6);
    }

    public void SetScaleOrigin(double e0, double e1, double e2)
    {
        scaleOrigin[0] = e0;
        scaleOrigin[1] = e1;
        scaleOrigin[2] = e2;
        Select(6);
    }

    public void SetScaleX(double scaleX_)
    {
        scaleX = scaleX_;
        Select(7);
    }

    public void SetScaleY(double scaleY_)
    {
        scaleY = scaleY_;
        Select(8);
    }

    public void SetScaleZ(double scaleZ_)
    {
        scaleZ = scaleZ_;
        Select(9);
    }

    public void SetDoTranslate(boolean doTranslate_)
    {
        doTranslate = doTranslate_;
        Select(10);
    }

    public void SetTranslateX(double translateX_)
    {
        translateX = translateX_;
        Select(11);
    }

    public void SetTranslateY(double translateY_)
    {
        translateY = translateY_;
        Select(12);
    }

    public void SetTranslateZ(double translateZ_)
    {
        translateZ = translateZ_;
        Select(13);
    }

    public void SetTransformType(int transformType_)
    {
        transformType = transformType_;
        Select(14);
    }

    public void SetInputCoordSys(int inputCoordSys_)
    {
        inputCoordSys = inputCoordSys_;
        Select(15);
    }

    public void SetOutputCoordSys(int outputCoordSys_)
    {
        outputCoordSys = outputCoordSys_;
        Select(16);
    }

    public void SetContinuousPhi(boolean continuousPhi_)
    {
        continuousPhi = continuousPhi_;
        Select(17);
    }

    public void SetM00(double m00_)
    {
        m00 = m00_;
        Select(18);
    }

    public void SetM01(double m01_)
    {
        m01 = m01_;
        Select(19);
    }

    public void SetM02(double m02_)
    {
        m02 = m02_;
        Select(20);
    }

    public void SetM03(double m03_)
    {
        m03 = m03_;
        Select(21);
    }

    public void SetM10(double m10_)
    {
        m10 = m10_;
        Select(22);
    }

    public void SetM11(double m11_)
    {
        m11 = m11_;
        Select(23);
    }

    public void SetM12(double m12_)
    {
        m12 = m12_;
        Select(24);
    }

    public void SetM13(double m13_)
    {
        m13 = m13_;
        Select(25);
    }

    public void SetM20(double m20_)
    {
        m20 = m20_;
        Select(26);
    }

    public void SetM21(double m21_)
    {
        m21 = m21_;
        Select(27);
    }

    public void SetM22(double m22_)
    {
        m22 = m22_;
        Select(28);
    }

    public void SetM23(double m23_)
    {
        m23 = m23_;
        Select(29);
    }

    public void SetM30(double m30_)
    {
        m30 = m30_;
        Select(30);
    }

    public void SetM31(double m31_)
    {
        m31 = m31_;
        Select(31);
    }

    public void SetM32(double m32_)
    {
        m32 = m32_;
        Select(32);
    }

    public void SetM33(double m33_)
    {
        m33 = m33_;
        Select(33);
    }

    public void SetInvertLinearTransform(boolean invertLinearTransform_)
    {
        invertLinearTransform = invertLinearTransform_;
        Select(34);
    }

    public void SetVectorTransformMethod(int vectorTransformMethod_)
    {
        vectorTransformMethod = vectorTransformMethod_;
        Select(35);
    }

    public void SetTransformVectors(boolean transformVectors_)
    {
        transformVectors = transformVectors_;
        Select(36);
    }

    // Property getting methods
    public boolean  GetDoRotate() { return doRotate; }
    public double[] GetRotateOrigin() { return rotateOrigin; }
    public double[] GetRotateAxis() { return rotateAxis; }
    public double   GetRotateAmount() { return rotateAmount; }
    public int      GetRotateType() { return rotateType; }
    public boolean  GetDoScale() { return doScale; }
    public double[] GetScaleOrigin() { return scaleOrigin; }
    public double   GetScaleX() { return scaleX; }
    public double   GetScaleY() { return scaleY; }
    public double   GetScaleZ() { return scaleZ; }
    public boolean  GetDoTranslate() { return doTranslate; }
    public double   GetTranslateX() { return translateX; }
    public double   GetTranslateY() { return translateY; }
    public double   GetTranslateZ() { return translateZ; }
    public int      GetTransformType() { return transformType; }
    public int      GetInputCoordSys() { return inputCoordSys; }
    public int      GetOutputCoordSys() { return outputCoordSys; }
    public boolean  GetContinuousPhi() { return continuousPhi; }
    public double   GetM00() { return m00; }
    public double   GetM01() { return m01; }
    public double   GetM02() { return m02; }
    public double   GetM03() { return m03; }
    public double   GetM10() { return m10; }
    public double   GetM11() { return m11; }
    public double   GetM12() { return m12; }
    public double   GetM13() { return m13; }
    public double   GetM20() { return m20; }
    public double   GetM21() { return m21; }
    public double   GetM22() { return m22; }
    public double   GetM23() { return m23; }
    public double   GetM30() { return m30; }
    public double   GetM31() { return m31; }
    public double   GetM32() { return m32; }
    public double   GetM33() { return m33; }
    public boolean  GetInvertLinearTransform() { return invertLinearTransform; }
    public int      GetVectorTransformMethod() { return vectorTransformMethod; }
    public boolean  GetTransformVectors() { return transformVectors; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteBool(doRotate);
        if(WriteSelect(1, buf))
            buf.WriteDoubleArray(rotateOrigin);
        if(WriteSelect(2, buf))
            buf.WriteDoubleArray(rotateAxis);
        if(WriteSelect(3, buf))
            buf.WriteDouble(rotateAmount);
        if(WriteSelect(4, buf))
            buf.WriteInt(rotateType);
        if(WriteSelect(5, buf))
            buf.WriteBool(doScale);
        if(WriteSelect(6, buf))
            buf.WriteDoubleArray(scaleOrigin);
        if(WriteSelect(7, buf))
            buf.WriteDouble(scaleX);
        if(WriteSelect(8, buf))
            buf.WriteDouble(scaleY);
        if(WriteSelect(9, buf))
            buf.WriteDouble(scaleZ);
        if(WriteSelect(10, buf))
            buf.WriteBool(doTranslate);
        if(WriteSelect(11, buf))
            buf.WriteDouble(translateX);
        if(WriteSelect(12, buf))
            buf.WriteDouble(translateY);
        if(WriteSelect(13, buf))
            buf.WriteDouble(translateZ);
        if(WriteSelect(14, buf))
            buf.WriteInt(transformType);
        if(WriteSelect(15, buf))
            buf.WriteInt(inputCoordSys);
        if(WriteSelect(16, buf))
            buf.WriteInt(outputCoordSys);
        if(WriteSelect(17, buf))
            buf.WriteBool(continuousPhi);
        if(WriteSelect(18, buf))
            buf.WriteDouble(m00);
        if(WriteSelect(19, buf))
            buf.WriteDouble(m01);
        if(WriteSelect(20, buf))
            buf.WriteDouble(m02);
        if(WriteSelect(21, buf))
            buf.WriteDouble(m03);
        if(WriteSelect(22, buf))
            buf.WriteDouble(m10);
        if(WriteSelect(23, buf))
            buf.WriteDouble(m11);
        if(WriteSelect(24, buf))
            buf.WriteDouble(m12);
        if(WriteSelect(25, buf))
            buf.WriteDouble(m13);
        if(WriteSelect(26, buf))
            buf.WriteDouble(m20);
        if(WriteSelect(27, buf))
            buf.WriteDouble(m21);
        if(WriteSelect(28, buf))
            buf.WriteDouble(m22);
        if(WriteSelect(29, buf))
            buf.WriteDouble(m23);
        if(WriteSelect(30, buf))
            buf.WriteDouble(m30);
        if(WriteSelect(31, buf))
            buf.WriteDouble(m31);
        if(WriteSelect(32, buf))
            buf.WriteDouble(m32);
        if(WriteSelect(33, buf))
            buf.WriteDouble(m33);
        if(WriteSelect(34, buf))
            buf.WriteBool(invertLinearTransform);
        if(WriteSelect(35, buf))
            buf.WriteInt(vectorTransformMethod);
        if(WriteSelect(36, buf))
            buf.WriteBool(transformVectors);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetDoRotate(buf.ReadBool());
            break;
        case 1:
            SetRotateOrigin(buf.ReadDoubleArray());
            break;
        case 2:
            SetRotateAxis(buf.ReadDoubleArray());
            break;
        case 3:
            SetRotateAmount(buf.ReadDouble());
            break;
        case 4:
            SetRotateType(buf.ReadInt());
            break;
        case 5:
            SetDoScale(buf.ReadBool());
            break;
        case 6:
            SetScaleOrigin(buf.ReadDoubleArray());
            break;
        case 7:
            SetScaleX(buf.ReadDouble());
            break;
        case 8:
            SetScaleY(buf.ReadDouble());
            break;
        case 9:
            SetScaleZ(buf.ReadDouble());
            break;
        case 10:
            SetDoTranslate(buf.ReadBool());
            break;
        case 11:
            SetTranslateX(buf.ReadDouble());
            break;
        case 12:
            SetTranslateY(buf.ReadDouble());
            break;
        case 13:
            SetTranslateZ(buf.ReadDouble());
            break;
        case 14:
            SetTransformType(buf.ReadInt());
            break;
        case 15:
            SetInputCoordSys(buf.ReadInt());
            break;
        case 16:
            SetOutputCoordSys(buf.ReadInt());
            break;
        case 17:
            SetContinuousPhi(buf.ReadBool());
            break;
        case 18:
            SetM00(buf.ReadDouble());
            break;
        case 19:
            SetM01(buf.ReadDouble());
            break;
        case 20:
            SetM02(buf.ReadDouble());
            break;
        case 21:
            SetM03(buf.ReadDouble());
            break;
        case 22:
            SetM10(buf.ReadDouble());
            break;
        case 23:
            SetM11(buf.ReadDouble());
            break;
        case 24:
            SetM12(buf.ReadDouble());
            break;
        case 25:
            SetM13(buf.ReadDouble());
            break;
        case 26:
            SetM20(buf.ReadDouble());
            break;
        case 27:
            SetM21(buf.ReadDouble());
            break;
        case 28:
            SetM22(buf.ReadDouble());
            break;
        case 29:
            SetM23(buf.ReadDouble());
            break;
        case 30:
            SetM30(buf.ReadDouble());
            break;
        case 31:
            SetM31(buf.ReadDouble());
            break;
        case 32:
            SetM32(buf.ReadDouble());
            break;
        case 33:
            SetM33(buf.ReadDouble());
            break;
        case 34:
            SetInvertLinearTransform(buf.ReadBool());
            break;
        case 35:
            SetVectorTransformMethod(buf.ReadInt());
            break;
        case 36:
            SetTransformVectors(buf.ReadBool());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + boolToString("doRotate", doRotate, indent) + "\n";
        str = str + doubleArrayToString("rotateOrigin", rotateOrigin, indent) + "\n";
        str = str + doubleArrayToString("rotateAxis", rotateAxis, indent) + "\n";
        str = str + doubleToString("rotateAmount", rotateAmount, indent) + "\n";
        str = str + indent + "rotateType = ";
        if(rotateType == ANGLETYPE_DEG)
            str = str + "ANGLETYPE_DEG";
        if(rotateType == ANGLETYPE_RAD)
            str = str + "ANGLETYPE_RAD";
        str = str + "\n";
        str = str + boolToString("doScale", doScale, indent) + "\n";
        str = str + doubleArrayToString("scaleOrigin", scaleOrigin, indent) + "\n";
        str = str + doubleToString("scaleX", scaleX, indent) + "\n";
        str = str + doubleToString("scaleY", scaleY, indent) + "\n";
        str = str + doubleToString("scaleZ", scaleZ, indent) + "\n";
        str = str + boolToString("doTranslate", doTranslate, indent) + "\n";
        str = str + doubleToString("translateX", translateX, indent) + "\n";
        str = str + doubleToString("translateY", translateY, indent) + "\n";
        str = str + doubleToString("translateZ", translateZ, indent) + "\n";
        str = str + indent + "transformType = ";
        if(transformType == TRANSFORMTYPE_SIMILARITY)
            str = str + "TRANSFORMTYPE_SIMILARITY";
        if(transformType == TRANSFORMTYPE_COORDINATE)
            str = str + "TRANSFORMTYPE_COORDINATE";
        if(transformType == TRANSFORMTYPE_LINEAR)
            str = str + "TRANSFORMTYPE_LINEAR";
        str = str + "\n";
        str = str + indent + "inputCoordSys = ";
        if(inputCoordSys == COORDINATESYSTEM_CARTESIAN)
            str = str + "COORDINATESYSTEM_CARTESIAN";
        if(inputCoordSys == COORDINATESYSTEM_CYLINDRICAL)
            str = str + "COORDINATESYSTEM_CYLINDRICAL";
        if(inputCoordSys == COORDINATESYSTEM_SPHERICAL)
            str = str + "COORDINATESYSTEM_SPHERICAL";
        str = str + "\n";
        str = str + indent + "outputCoordSys = ";
        if(outputCoordSys == COORDINATESYSTEM_CARTESIAN)
            str = str + "COORDINATESYSTEM_CARTESIAN";
        if(outputCoordSys == COORDINATESYSTEM_CYLINDRICAL)
            str = str + "COORDINATESYSTEM_CYLINDRICAL";
        if(outputCoordSys == COORDINATESYSTEM_SPHERICAL)
            str = str + "COORDINATESYSTEM_SPHERICAL";
        str = str + "\n";
        str = str + boolToString("continuousPhi", continuousPhi, indent) + "\n";
        str = str + doubleToString("m00", m00, indent) + "\n";
        str = str + doubleToString("m01", m01, indent) + "\n";
        str = str + doubleToString("m02", m02, indent) + "\n";
        str = str + doubleToString("m03", m03, indent) + "\n";
        str = str + doubleToString("m10", m10, indent) + "\n";
        str = str + doubleToString("m11", m11, indent) + "\n";
        str = str + doubleToString("m12", m12, indent) + "\n";
        str = str + doubleToString("m13", m13, indent) + "\n";
        str = str + doubleToString("m20", m20, indent) + "\n";
        str = str + doubleToString("m21", m21, indent) + "\n";
        str = str + doubleToString("m22", m22, indent) + "\n";
        str = str + doubleToString("m23", m23, indent) + "\n";
        str = str + doubleToString("m30", m30, indent) + "\n";
        str = str + doubleToString("m31", m31, indent) + "\n";
        str = str + doubleToString("m32", m32, indent) + "\n";
        str = str + doubleToString("m33", m33, indent) + "\n";
        str = str + boolToString("invertLinearTransform", invertLinearTransform, indent) + "\n";
        str = str + indent + "vectorTransformMethod = ";
        if(vectorTransformMethod == VECTORTRANSFORMMETHOD_NONE)
            str = str + "VECTORTRANSFORMMETHOD_NONE";
        if(vectorTransformMethod == VECTORTRANSFORMMETHOD_ASPOINT)
            str = str + "VECTORTRANSFORMMETHOD_ASPOINT";
        if(vectorTransformMethod == VECTORTRANSFORMMETHOD_ASDISPLACEMENT)
            str = str + "VECTORTRANSFORMMETHOD_ASDISPLACEMENT";
        if(vectorTransformMethod == VECTORTRANSFORMMETHOD_ASDIRECTION)
            str = str + "VECTORTRANSFORMMETHOD_ASDIRECTION";
        str = str + "\n";
        str = str + boolToString("transformVectors", transformVectors, indent) + "\n";
        return str;
    }


    // Attributes
    private boolean  doRotate;
    private double[] rotateOrigin;
    private double[] rotateAxis;
    private double   rotateAmount;
    private int      rotateType;
    private boolean  doScale;
    private double[] scaleOrigin;
    private double   scaleX;
    private double   scaleY;
    private double   scaleZ;
    private boolean  doTranslate;
    private double   translateX;
    private double   translateY;
    private double   translateZ;
    private int      transformType;
    private int      inputCoordSys;
    private int      outputCoordSys;
    private boolean  continuousPhi;
    private double   m00;
    private double   m01;
    private double   m02;
    private double   m03;
    private double   m10;
    private double   m11;
    private double   m12;
    private double   m13;
    private double   m20;
    private double   m21;
    private double   m22;
    private double   m23;
    private double   m30;
    private double   m31;
    private double   m32;
    private double   m33;
    private boolean  invertLinearTransform;
    private int      vectorTransformMethod;
    private boolean  transformVectors;
}

