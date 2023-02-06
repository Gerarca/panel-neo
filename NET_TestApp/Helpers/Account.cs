using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;

namespace NET_TestApp
{
    public class Account
    {
        #region Variables
        private object _lock                  = new object();
        private string _identifier            = string.Empty;
        private string _integrationid         = string.Empty;
        private string _integrationaccesscode = string.Empty;
        private string _udpchannelfunction    = string.Empty;
        private string _tcpchannelfunction    = string.Empty;
        private string _installercode         = string.Empty;
        private UInt32 _keychangetime         = 0;
        #endregion

        #region Constructor
        public Account()
        {
        }

        public Account(string identifier, string integrationid, string integrationcode, string udpchannelfunction, string tcpchannelfunction, string installercode, UInt32 keychangetime)
        {
            this.Identifier = identifier;
            this.IntegrationId = integrationid;
            this.IntegrationAccessCode = integrationcode;
            this.UdpChannelFunction = udpchannelfunction;
            this.TcpChannelFunction = tcpchannelfunction;
            this.InstallerCode = installercode;
            this.KeyChangeTime = keychangetime;
        }

        public Account(Account other)
        {
            this.Identifier = other.Identifier;
            this.IntegrationId = other.IntegrationId;
            this.IntegrationAccessCode = other.IntegrationAccessCode;
            this.UdpChannelFunction = other.UdpChannelFunction;
            this.TcpChannelFunction = other.TcpChannelFunction;
            this.InstallerCode = other.InstallerCode;
            this.KeyChangeTime = other.KeyChangeTime;
        }
        #endregion

        #region Properties
        public string Identifier
        {
            get { lock (_lock) { return (_identifier); } }
            set { lock (_lock) { _identifier = value; } }
        }

        public string IntegrationId
        {
            get { lock (_lock) { return (_integrationid); } }
            set { lock (_lock) { _integrationid = value; } }
        }

        public string IntegrationAccessCode
        {
            get { lock (_lock) { return (_integrationaccesscode); } }
            set { lock (_lock) { _integrationaccesscode = value; } }
        }

        public string UdpChannelFunction
        {
            get { lock (_lock) { return (_udpchannelfunction); } }
            set { lock (_lock) { _udpchannelfunction = value; } }
        }

        public string TcpChannelFunction
        {
            get { lock (_lock) { return (_tcpchannelfunction); } }
            set { lock (_lock) { _tcpchannelfunction = value; } }
        }

        public string InstallerCode
        {
            get { lock (_lock) { return (_installercode); } }
            set { lock (_lock) { _installercode = value; } }
        }

        public UInt32 KeyChangeTime
        {
            get { lock (_lock) { return (_keychangetime); } }
            set { lock (_lock) { _keychangetime = value; } }
        }
        #endregion
    }
}
