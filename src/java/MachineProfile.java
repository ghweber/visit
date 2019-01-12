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

package llnl.visit;

import java.util.Vector;

// ****************************************************************************
// Class: MachineProfile
//
// Purpose:
//    This class contains information about a host for a remote VisIt engine.
//
// Notes:      Autogenerated by xml2java.
//
// Programmer: xml2java
// Creation:   omitted
//
// Modifications:
//   
// ****************************************************************************

public class MachineProfile extends AttributeSubject
{
    private static int MachineProfile_numAdditionalAtts = 22;

    // Enum values
    public final static int CLIENTHOSTDETERMINATION_MACHINENAME = 0;
    public final static int CLIENTHOSTDETERMINATION_MANUALLYSPECIFIED = 1;
    public final static int CLIENTHOSTDETERMINATION_PARSEDFROMSSHCLIENT = 2;


    public MachineProfile()
    {
        super(MachineProfile_numAdditionalAtts);

        host = new String("localhost");
        userName = new String("notset");
        password = new String("");
        hostAliases = new String("");
        hostNickname = new String("");
        directory = new String("");
        shareOneBatchJob = false;
        sshPortSpecified = false;
        sshPort = 22;
        sshCommandSpecified = false;
        sshCommand = new Vector();
        sshCommand.addElement(new String("ssh"));
        useGateway = false;
        gatewayHost = new String("");
        clientHostDetermination = CLIENTHOSTDETERMINATION_MACHINENAME;
        manualClientHostName = new String("");
        tunnelSSH = false;
        maximumNodesValid = false;
        maximumNodes = 1;
        maximumProcessorsValid = false;
        maximumProcessors = 1;
        launchProfiles = new Vector();
        activeProfile = -1;
    }

    public MachineProfile(int nMoreFields)
    {
        super(MachineProfile_numAdditionalAtts + nMoreFields);

        host = new String("localhost");
        userName = new String("notset");
        password = new String("");
        hostAliases = new String("");
        hostNickname = new String("");
        directory = new String("");
        shareOneBatchJob = false;
        sshPortSpecified = false;
        sshPort = 22;
        sshCommandSpecified = false;
        sshCommand = new Vector();
        sshCommand.addElement(new String("ssh"));
        useGateway = false;
        gatewayHost = new String("");
        clientHostDetermination = CLIENTHOSTDETERMINATION_MACHINENAME;
        manualClientHostName = new String("");
        tunnelSSH = false;
        maximumNodesValid = false;
        maximumNodes = 1;
        maximumProcessorsValid = false;
        maximumProcessors = 1;
        launchProfiles = new Vector();
        activeProfile = -1;
    }

    public MachineProfile(MachineProfile obj)
    {
        super(obj);

        int i;

        host = new String(obj.host);
        userName = new String(obj.userName);
        password = new String(obj.password);
        hostAliases = new String(obj.hostAliases);
        hostNickname = new String(obj.hostNickname);
        directory = new String(obj.directory);
        shareOneBatchJob = obj.shareOneBatchJob;
        sshPortSpecified = obj.sshPortSpecified;
        sshPort = obj.sshPort;
        sshCommandSpecified = obj.sshCommandSpecified;
        sshCommand = new Vector(obj.sshCommand.size());
        for(i = 0; i < obj.sshCommand.size(); ++i)
            sshCommand.addElement(new String((String)obj.sshCommand.elementAt(i)));

        useGateway = obj.useGateway;
        gatewayHost = new String(obj.gatewayHost);
        clientHostDetermination = obj.clientHostDetermination;
        manualClientHostName = new String(obj.manualClientHostName);
        tunnelSSH = obj.tunnelSSH;
        maximumNodesValid = obj.maximumNodesValid;
        maximumNodes = obj.maximumNodes;
        maximumProcessorsValid = obj.maximumProcessorsValid;
        maximumProcessors = obj.maximumProcessors;
        // *** Copy the launchProfiles field ***
        launchProfiles = new Vector(obj.launchProfiles.size());
        for(i = 0; i < obj.launchProfiles.size(); ++i)
        {
            LaunchProfile oldObj = (LaunchProfile)obj.launchProfiles.elementAt(i);
            launchProfiles.addElement(new LaunchProfile(oldObj));
        }

        activeProfile = obj.activeProfile;

        SelectAll();
    }

    public int Offset()
    {
        return super.Offset() + super.GetNumAdditionalAttributes();
    }

    public int GetNumAdditionalAttributes()
    {
        return MachineProfile_numAdditionalAtts;
    }

    public boolean equals(MachineProfile obj)
    {
        int i;

        // Compare the elements in the sshCommand vector.
        boolean sshCommand_equal = (obj.sshCommand.size() == sshCommand.size());
        for(i = 0; (i < sshCommand.size()) && sshCommand_equal; ++i)
        {
            // Make references to String from Object.
            String sshCommand1 = (String)sshCommand.elementAt(i);
            String sshCommand2 = (String)obj.sshCommand.elementAt(i);
            sshCommand_equal = sshCommand1.equals(sshCommand2);
        }
        // Compare the elements in the launchProfiles vector.
        boolean launchProfiles_equal = (obj.launchProfiles.size() == launchProfiles.size());
        for(i = 0; (i < launchProfiles.size()) && launchProfiles_equal; ++i)
        {
            // Make references to LaunchProfile from Object.
            LaunchProfile launchProfiles1 = (LaunchProfile)launchProfiles.elementAt(i);
            LaunchProfile launchProfiles2 = (LaunchProfile)obj.launchProfiles.elementAt(i);
            launchProfiles_equal = launchProfiles1.equals(launchProfiles2);
        }
        // Create the return value
        return ((host.equals(obj.host)) &&
                (userName.equals(obj.userName)) &&
                (password.equals(obj.password)) &&
                (hostAliases.equals(obj.hostAliases)) &&
                (hostNickname.equals(obj.hostNickname)) &&
                (directory.equals(obj.directory)) &&
                (shareOneBatchJob == obj.shareOneBatchJob) &&
                (sshPortSpecified == obj.sshPortSpecified) &&
                (sshPort == obj.sshPort) &&
                (sshCommandSpecified == obj.sshCommandSpecified) &&
                sshCommand_equal &&
                (useGateway == obj.useGateway) &&
                (gatewayHost.equals(obj.gatewayHost)) &&
                (clientHostDetermination == obj.clientHostDetermination) &&
                (manualClientHostName.equals(obj.manualClientHostName)) &&
                (tunnelSSH == obj.tunnelSSH) &&
                (maximumNodesValid == obj.maximumNodesValid) &&
                (maximumNodes == obj.maximumNodes) &&
                (maximumProcessorsValid == obj.maximumProcessorsValid) &&
                (maximumProcessors == obj.maximumProcessors) &&
                launchProfiles_equal &&
                (activeProfile == obj.activeProfile));
    }

    // Property setting methods
    public void SetHost(String host_)
    {
        host = host_;
        Select(0);
    }

    public void SetUserName(String userName_)
    {
        userName = userName_;
        Select(1);
    }

    public void SetPassword(String password_)
    {
        password = password_;
        Select(2);
    }

    public void SetHostAliases(String hostAliases_)
    {
        hostAliases = hostAliases_;
        Select(3);
    }

    public void SetHostNickname(String hostNickname_)
    {
        hostNickname = hostNickname_;
        Select(4);
    }

    public void SetDirectory(String directory_)
    {
        directory = directory_;
        Select(5);
    }

    public void SetShareOneBatchJob(boolean shareOneBatchJob_)
    {
        shareOneBatchJob = shareOneBatchJob_;
        Select(6);
    }

    public void SetSshPortSpecified(boolean sshPortSpecified_)
    {
        sshPortSpecified = sshPortSpecified_;
        Select(7);
    }

    public void SetSshPort(int sshPort_)
    {
        sshPort = sshPort_;
        Select(8);
    }

    public void SetSshCommandSpecified(boolean sshCommandSpecified_)
    {
        sshCommandSpecified = sshCommandSpecified_;
        Select(9);
    }

    public void SetSshCommand(Vector sshCommand_)
    {
        sshCommand = sshCommand_;
        Select(10);
    }

    public void SetUseGateway(boolean useGateway_)
    {
        useGateway = useGateway_;
        Select(11);
    }

    public void SetGatewayHost(String gatewayHost_)
    {
        gatewayHost = gatewayHost_;
        Select(12);
    }

    public void SetClientHostDetermination(int clientHostDetermination_)
    {
        clientHostDetermination = clientHostDetermination_;
        Select(13);
    }

    public void SetManualClientHostName(String manualClientHostName_)
    {
        manualClientHostName = manualClientHostName_;
        Select(14);
    }

    public void SetTunnelSSH(boolean tunnelSSH_)
    {
        tunnelSSH = tunnelSSH_;
        Select(15);
    }

    public void SetMaximumNodesValid(boolean maximumNodesValid_)
    {
        maximumNodesValid = maximumNodesValid_;
        Select(16);
    }

    public void SetMaximumNodes(int maximumNodes_)
    {
        maximumNodes = maximumNodes_;
        Select(17);
    }

    public void SetMaximumProcessorsValid(boolean maximumProcessorsValid_)
    {
        maximumProcessorsValid = maximumProcessorsValid_;
        Select(18);
    }

    public void SetMaximumProcessors(int maximumProcessors_)
    {
        maximumProcessors = maximumProcessors_;
        Select(19);
    }

    public void SetActiveProfile(int activeProfile_)
    {
        activeProfile = activeProfile_;
        Select(21);
    }

    // Property getting methods
    public String  GetHost() { return host; }
    public String  GetUserName() { return userName; }
    public String  GetPassword() { return password; }
    public String  GetHostAliases() { return hostAliases; }
    public String  GetHostNickname() { return hostNickname; }
    public String  GetDirectory() { return directory; }
    public boolean GetShareOneBatchJob() { return shareOneBatchJob; }
    public boolean GetSshPortSpecified() { return sshPortSpecified; }
    public int     GetSshPort() { return sshPort; }
    public boolean GetSshCommandSpecified() { return sshCommandSpecified; }
    public Vector  GetSshCommand() { return sshCommand; }
    public boolean GetUseGateway() { return useGateway; }
    public String  GetGatewayHost() { return gatewayHost; }
    public int     GetClientHostDetermination() { return clientHostDetermination; }
    public String  GetManualClientHostName() { return manualClientHostName; }
    public boolean GetTunnelSSH() { return tunnelSSH; }
    public boolean GetMaximumNodesValid() { return maximumNodesValid; }
    public int     GetMaximumNodes() { return maximumNodes; }
    public boolean GetMaximumProcessorsValid() { return maximumProcessorsValid; }
    public int     GetMaximumProcessors() { return maximumProcessors; }
    public Vector  GetLaunchProfiles() { return launchProfiles; }
    public int     GetActiveProfile() { return activeProfile; }

    // Write and read methods.
    public void WriteAtts(CommunicationBuffer buf)
    {
        if(WriteSelect(0, buf))
            buf.WriteString(host);
        if(WriteSelect(1, buf))
            buf.WriteString(userName);
        if(WriteSelect(2, buf))
            buf.WriteString(password);
        if(WriteSelect(3, buf))
            buf.WriteString(hostAliases);
        if(WriteSelect(4, buf))
            buf.WriteString(hostNickname);
        if(WriteSelect(5, buf))
            buf.WriteString(directory);
        if(WriteSelect(6, buf))
            buf.WriteBool(shareOneBatchJob);
        if(WriteSelect(7, buf))
            buf.WriteBool(sshPortSpecified);
        if(WriteSelect(8, buf))
            buf.WriteInt(sshPort);
        if(WriteSelect(9, buf))
            buf.WriteBool(sshCommandSpecified);
        if(WriteSelect(10, buf))
            buf.WriteStringVector(sshCommand);
        if(WriteSelect(11, buf))
            buf.WriteBool(useGateway);
        if(WriteSelect(12, buf))
            buf.WriteString(gatewayHost);
        if(WriteSelect(13, buf))
            buf.WriteInt(clientHostDetermination);
        if(WriteSelect(14, buf))
            buf.WriteString(manualClientHostName);
        if(WriteSelect(15, buf))
            buf.WriteBool(tunnelSSH);
        if(WriteSelect(16, buf))
            buf.WriteBool(maximumNodesValid);
        if(WriteSelect(17, buf))
            buf.WriteInt(maximumNodes);
        if(WriteSelect(18, buf))
            buf.WriteBool(maximumProcessorsValid);
        if(WriteSelect(19, buf))
            buf.WriteInt(maximumProcessors);
        if(WriteSelect(20, buf))
        {
            buf.WriteInt(launchProfiles.size());
            for(int i = 0; i < launchProfiles.size(); ++i)
            {
                LaunchProfile tmp = (LaunchProfile)launchProfiles.elementAt(i);
                tmp.Write(buf);
            }
        }
        if(WriteSelect(21, buf))
            buf.WriteInt(activeProfile);
    }

    public void ReadAtts(int index, CommunicationBuffer buf)
    {
        switch(index)
        {
        case 0:
            SetHost(buf.ReadString());
            break;
        case 1:
            SetUserName(buf.ReadString());
            break;
        case 2:
            SetPassword(buf.ReadString());
            break;
        case 3:
            SetHostAliases(buf.ReadString());
            break;
        case 4:
            SetHostNickname(buf.ReadString());
            break;
        case 5:
            SetDirectory(buf.ReadString());
            break;
        case 6:
            SetShareOneBatchJob(buf.ReadBool());
            break;
        case 7:
            SetSshPortSpecified(buf.ReadBool());
            break;
        case 8:
            SetSshPort(buf.ReadInt());
            break;
        case 9:
            SetSshCommandSpecified(buf.ReadBool());
            break;
        case 10:
            SetSshCommand(buf.ReadStringVector());
            break;
        case 11:
            SetUseGateway(buf.ReadBool());
            break;
        case 12:
            SetGatewayHost(buf.ReadString());
            break;
        case 13:
            SetClientHostDetermination(buf.ReadInt());
            break;
        case 14:
            SetManualClientHostName(buf.ReadString());
            break;
        case 15:
            SetTunnelSSH(buf.ReadBool());
            break;
        case 16:
            SetMaximumNodesValid(buf.ReadBool());
            break;
        case 17:
            SetMaximumNodes(buf.ReadInt());
            break;
        case 18:
            SetMaximumProcessorsValid(buf.ReadBool());
            break;
        case 19:
            SetMaximumProcessors(buf.ReadInt());
            break;
        case 20:
            {
                int len = buf.ReadInt();
                launchProfiles.clear();
                for(int j = 0; j < len; ++j)
                {
                    LaunchProfile tmp = new LaunchProfile();
                    tmp.Read(buf);
                    launchProfiles.addElement(tmp);
                }
            }
            Select(20);
            break;
        case 21:
            SetActiveProfile(buf.ReadInt());
            break;
        }
    }

    public String toString(String indent)
    {
        String str = new String();
        str = str + stringToString("host", host, indent) + "\n";
        str = str + stringToString("userName", userName, indent) + "\n";
        str = str + stringToString("password", password, indent) + "\n";
        str = str + stringToString("hostAliases", hostAliases, indent) + "\n";
        str = str + stringToString("hostNickname", hostNickname, indent) + "\n";
        str = str + stringToString("directory", directory, indent) + "\n";
        str = str + boolToString("shareOneBatchJob", shareOneBatchJob, indent) + "\n";
        str = str + boolToString("sshPortSpecified", sshPortSpecified, indent) + "\n";
        str = str + intToString("sshPort", sshPort, indent) + "\n";
        str = str + boolToString("sshCommandSpecified", sshCommandSpecified, indent) + "\n";
        str = str + stringVectorToString("sshCommand", sshCommand, indent) + "\n";
        str = str + boolToString("useGateway", useGateway, indent) + "\n";
        str = str + stringToString("gatewayHost", gatewayHost, indent) + "\n";
        str = str + indent + "clientHostDetermination = ";
        if(clientHostDetermination == CLIENTHOSTDETERMINATION_MACHINENAME)
            str = str + "CLIENTHOSTDETERMINATION_MACHINENAME";
        if(clientHostDetermination == CLIENTHOSTDETERMINATION_MANUALLYSPECIFIED)
            str = str + "CLIENTHOSTDETERMINATION_MANUALLYSPECIFIED";
        if(clientHostDetermination == CLIENTHOSTDETERMINATION_PARSEDFROMSSHCLIENT)
            str = str + "CLIENTHOSTDETERMINATION_PARSEDFROMSSHCLIENT";
        str = str + "\n";
        str = str + stringToString("manualClientHostName", manualClientHostName, indent) + "\n";
        str = str + boolToString("tunnelSSH", tunnelSSH, indent) + "\n";
        str = str + boolToString("maximumNodesValid", maximumNodesValid, indent) + "\n";
        str = str + intToString("maximumNodes", maximumNodes, indent) + "\n";
        str = str + boolToString("maximumProcessorsValid", maximumProcessorsValid, indent) + "\n";
        str = str + intToString("maximumProcessors", maximumProcessors, indent) + "\n";
        str = str + indent + "launchProfiles = {\n";
        for(int i = 0; i < launchProfiles.size(); ++i)
        {
            AttributeSubject s = (AttributeSubject)launchProfiles.elementAt(i);
            str = str + s.toString(indent + "    ");
            if(i < launchProfiles.size()-1)
                str = str + ", ";
            str = str + "\n";
        }
        str = str + "}\n";
        str = str + intToString("activeProfile", activeProfile, indent) + "\n";
        return str;
    }

    // Attributegroup convenience methods
    public void AddLaunchProfiles(LaunchProfile obj)
    {
        launchProfiles.addElement(new LaunchProfile(obj));
        Select(20);
    }

    public void ClearLaunchProfiles()
    {
        launchProfiles.clear();
        Select(20);
    }

    public void RemoveLaunchProfiles(int index)
    {
        if(index >= 0 && index < launchProfiles.size())
        {
            launchProfiles.remove(index);
            Select(20);
        }
    }

    public int GetNumLaunchProfiles()
    {
        return launchProfiles.size();
    }

    public LaunchProfile GetLaunchProfiles(int i)
    {
        LaunchProfile tmp = (LaunchProfile)launchProfiles.elementAt(i);
        return tmp;
    }


    // Attributes
    private String  host;
    private String  userName;
    private String  password;
    private String  hostAliases;
    private String  hostNickname;
    private String  directory;
    private boolean shareOneBatchJob;
    private boolean sshPortSpecified;
    private int     sshPort;
    private boolean sshCommandSpecified;
    private Vector  sshCommand; // vector of String objects
    private boolean useGateway;
    private String  gatewayHost;
    private int     clientHostDetermination;
    private String  manualClientHostName;
    private boolean tunnelSSH;
    private boolean maximumNodesValid;
    private int     maximumNodes;
    private boolean maximumProcessorsValid;
    private int     maximumProcessors;
    private Vector  launchProfiles; // vector of LaunchProfile objects
    private int     activeProfile;
}

