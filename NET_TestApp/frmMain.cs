using System;
using System.Collections.Generic;
using System.ComponentModel;
using System.Data;
using System.Drawing;
using System.Linq;
using System.Text;
using System.Windows.Forms;
using System.Net;
using System.Net.Sockets;
using System.Reflection;
using System.Threading;
using System.Diagnostics;
using System.IO;
using System.Timers;
using DSC.Automation.TextHelpers;
using TSP.DSC_InteractiveSDK;
using TSP.DSC_InteractiveSDK.Security;
using NET_TestApp.Helpers;

namespace NET_TestApp
{
    public partial class frmMain : Form
    {
        #region Variables
        private InteractiveServices         _services      = null; // interactive services object
        private CancellationTokenSource     _ctokensource  = null;
        private Thread                      _thdDebug      = null;
        private List<string>                _msgQueue      = new List<string>();
        private Dictionary<string, Account> _accounts      = new Dictionary<string, Account>();
        #endregion

        #region Constructor
        public frmMain()
        {
            InitializeComponent();
        }
        #endregion

        #region Form Events
        private void frmMain_Load(object sender, EventArgs e)
        {
            try
            {
                tstbIP.Enabled = true;
                tstbUDP.Enabled = true;
                tstbTCP.Enabled = true;
                tsbStart.Enabled = true;
                tsbStop.Enabled = false;
                tsbAdd.Enabled = true;
                lvSecurityBases_SelectedIndexChanged(lvSecurityBases, null); //habilita o deshabilita botones editar y remover

                LoadConfig();

                tstbIP.Text = getMachineIP();

                // load security bases to ui
                LoadSecurityBaseDisplay();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
                this.BeginInvoke(new MethodInvoker(this.Close));
            } // try
        }

        private void frmMain_FormClosing(object sender, FormClosingEventArgs e)
        {
            tsbStop_Click(this, null);

            SaveConfig();
        }

        private void tsbAdd_Click(object sender, EventArgs e)
        {
            using (frmAdd f = new frmAdd(_accounts, null))
            {
                if (f.ShowDialog(this) == DialogResult.OK)
                {
                    LoadSecurityBaseDisplay();
                }
            }
            lvSecurityBases_SelectedIndexChanged(lvSecurityBases, null);
            SaveConfig();
        }

        private void tsbRemove_Click(object sender, EventArgs e)
        {
            if (lvSecurityBases.SelectedItems.Count > 0)
            {
                foreach (ListViewItem i in lvSecurityBases.SelectedItems)
                {
                    if (_accounts != null)
                    {
                        _accounts.Remove(i.SubItems[0].Text);
                    }
                }
                LoadSecurityBaseDisplay();
            }
            lvSecurityBases_SelectedIndexChanged(lvSecurityBases, null);
            SaveConfig();
        }

        private void tsbEdit_Click(object sender, EventArgs e)
        {
            if (lvSecurityBases.SelectedItems.Count > 0)
            {
                if (_accounts != null)
                {
                    Account a = _accounts[lvSecurityBases.SelectedItems[0].SubItems[0].Text];
                    if (a != null)
                    {
                        using (frmAdd f = new frmAdd(_accounts, a))
                        {
                            if (f.ShowDialog(this) == DialogResult.OK)
                            {
                                LoadSecurityBaseDisplay();
                            }
                        }
                    }
                }
            }
            lvSecurityBases_SelectedIndexChanged(lvSecurityBases, null);
            SaveConfig();
        }

        private void tsbStart_Click(object sender, EventArgs e)
        {
            try
            {
                // activate interactive services
                if (_services == null)
                {
                    _services = new InteractiveServices();
                    foreach (KeyValuePair<string, Account> kvp in _accounts)
                    {
                        _services.AddAccount(kvp.Value);
                    }
                }

                DebugStart();

                _services.DebugEvent += new EventHandler<DebugEventArgs>(_services_DebugEvent);
                _services.ExceptionEvent += new EventHandler<ExceptionEventArgs>(_services_ExceptionEvent);
                _services.SecurityBaseUpdateEvent += new EventHandler<SecurityBaseUpdateEventArgs>(_services_SecurityBaseUpdateEvent);
                _services.Activate(tstbIP.Text, Convert.ToInt32(tstbUDP.Text), Convert.ToInt32(tstbTCP.Text));

                tstbIP.Enabled = false;
                tstbUDP.Enabled = false;
                tstbTCP.Enabled = false;
                tsbStart.Enabled = false;
                tsbStop.Enabled = true;
                tsbAdd.Enabled = false;
                lvSecurityBases_SelectedIndexChanged(lvSecurityBases, null);
                SaveConfig();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void tsbStop_Click(object sender, EventArgs e)
        {
            try
            {
                if (_services != null)
                {
                    // shutdown interactive services
                    _services.Shutdown();
                    _services.SecurityBaseUpdateEvent -= new EventHandler<SecurityBaseUpdateEventArgs>(_services_SecurityBaseUpdateEvent);
                    _services.ExceptionEvent -= new EventHandler<ExceptionEventArgs>(_services_ExceptionEvent);
                    _services.DebugEvent -= new EventHandler<DebugEventArgs>(_services_DebugEvent);
                    _services = null;

                    DebugStop();

                    tstbIP.Enabled = true;
                    tstbUDP.Enabled = true;
                    tstbTCP.Enabled = true;
                    tsbStop.Enabled = false;
                    tsbStart.Enabled = true;
                    tsbAdd.Enabled = true;
                    lvSecurityBases_SelectedIndexChanged(lvSecurityBases, null);
                }
                LoadSecurityBaseDisplay();
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void lvSecurityBases_MouseDoubleClick(object sender, MouseEventArgs e)
        {
            if (e.Button == MouseButtons.Left)
            {
                // open the securitybase form only if the security base has successfully been connected to by the panel
                string key = lvSecurityBases.SelectedItems[0].Name;
                if (lvSecurityBases.SelectedItems[0].ImageIndex == 1) // connected
                {
                    if (_services != null)
                    {
                        if (_services.SecurityBases.ContainsKey(key) == true)
                        {
                            if (FormUtils.IsFormOpen(key) == false)
                            {
                                frmSecurityBase f = new frmSecurityBase(_services.sdk, key, _services.SecurityBases[key]);
                                f.Show();
                            } // if
                        } // if
                    }
                }
            } // if
        }

        private void lvSecurityBases_SelectedIndexChanged(object sender, EventArgs e)
        {
            if (((sender as ListViewNF).SelectedIndices.Count > 0) && (tsbStart.Enabled == true))
            {
                tsbRemove.Enabled = true;
                tsbEdit.Enabled = true;

            }
            else
            {
                tsbRemove.Enabled = false;
                tsbEdit.Enabled = false;
            }
        }
        #endregion

        #region Private Events
        private void _services_DebugEvent(object sender, DebugEventArgs e)
        {
            string id = string.Empty;
            if (sender is ISecurityBase)
            {
                IRepository rep = (sender as ISecurityBase).Repository;
                id = "[" + rep.PeerIdentifier + "] ";
                rep.Dispose();
            }
            else if (sender is IChannel)
            {
                id = "[" + (sender as IChannel).PeerIdentifier + "] ";
            }
            AddToDebugQueue(id + e.msg);
        }

        private void _services_ExceptionEvent(object sender, ExceptionEventArgs e)
        {
            string id = string.Empty;
            if (sender is ISecurityBase)
            {
                IRepository rep = (sender as ISecurityBase).Repository;
                id = "[" + rep.PeerIdentifier + "] ";
                rep.Dispose();

            }
            else if (sender is IChannel)
            {
                id = "[" + (sender as IChannel).PeerIdentifier + "] ";
            }
            AddToDebugQueue(id + "[Exception Event]\r\n" +
                "Sender   : " + sender.ToString() + "\r\n" +
                "Exception: \r\n\r\n" +
                "   Message       : " + e.Exception.Message.ToString() + "\r\n" +
                "   InnerException: " + ((e.Exception.InnerException != null) ? e.Exception.InnerException.ToString() : "N/A") + "\r\n" +
                "   StackTrace    : " + ((e.Exception.StackTrace != null) ? e.Exception.StackTrace.ToString() : "N/A") + "\r\n" +
                "   Source        : " + ((e.Exception.Source != null) ? e.Exception.Source.ToString() : "N/A") + "\r\n\r\n");
        }

        private void _services_SecurityBaseUpdateEvent(object sender, SecurityBaseUpdateEventArgs e)
        {
            UpdateSecurityBaseDisplayItem(e.identifier, e.status);
        }
        #endregion

        #region Private Methods
        private string getMachineIP()
        {
            string localip = "127.0.0.1";
            try
            {
                // quick and easy way to get machine address
                using (Socket socket = new Socket(AddressFamily.InterNetwork, SocketType.Dgram, System.Net.Sockets.ProtocolType.Udp))
                {
                    if (socket != null)
                    {
                        socket.Connect("8.8.8.8", 55555);
                        IPEndPoint endPoint = (socket.LocalEndPoint as IPEndPoint);
                        if (endPoint != null)
                        {
                            localip = endPoint.Address.ToString();
                        } // if
                    } // if
                } // using
            }
            catch (Exception)
            {
                // return default ip
            } // try

            return localip;
        }

        private void Log(string message)
        {
            // log message to file
            try
            {
                using (StreamWriter file = new StreamWriter("debug.log", true))
                {
                    if (file != null)
                    {
                        file.Write(message);
                    } // if
                } // using
            }
            catch (Exception)
            {
            } // try
        }

        private void DebugStart()
        {
            _msgQueue.Clear();
            _ctokensource = new CancellationTokenSource();
            _thdDebug = new Thread(() => DebugOperations(_ctokensource.Token));
            _thdDebug.Name = "Debug";
            _thdDebug.Start();
        }

        private void DebugStop()
        {
            // stop the processing thread
            if (_ctokensource != null)
            {
                _ctokensource.Cancel();
            } // if

            // wait for thread to stop
            if (_thdDebug != null)
            {
                while (_thdDebug.IsAlive) { Thread.Sleep(100); };
            } // if
            _msgQueue.Clear();
        }

        private void AddToDebugQueue(string msg)
        {
            lock (_msgQueue)
            {
                _msgQueue.Add("[" + DateTime.Now.ToString("hh:mm:ss.fff") + "] " + msg);
            }
        }

        private void LoadSecurityBaseDisplay()
        {
            // create the security base display items from the accounts list
            lvSecurityBases.Clear();
            lvSecurityBases.BeginUpdate();
            lvSecurityBases.Columns.AddRange(new ColumnHeader[] { new ColumnHeader(), new ColumnHeader(), new ColumnHeader(), new ColumnHeader(), new ColumnHeader(), new ColumnHeader(), new ColumnHeader() });
            List<ListViewItem> securitybases = new List<ListViewItem>();
            foreach (string key in _accounts.Keys)
            {
                ListViewItem lvi = new ListViewItem(new string[] { _accounts[key].Identifier, _accounts[key].IntegrationAccessCode }, 0);
                lvi.UseItemStyleForSubItems = false;
                lvi.Font = lvSecurityBases.Font;
                lvi.Name = _accounts[key].Identifier;
                lvi.SubItems[0].ForeColor = Color.Black;
                lvi.SubItems[1].ForeColor = Color.Gray;
                securitybases.Add(lvi);
            } // foreach
            lvSecurityBases.Items.AddRange(securitybases.ToArray());
            lvSecurityBases.EndUpdate();
        }

        private void UpdateSecurityBaseDisplayItem(string identifier, SecurityBaseStatus status)
        {
            if (lvSecurityBases.InvokeRequired)
            {
                lvSecurityBases.BeginInvoke(new MethodInvoker(delegate() { UpdateSecurityBaseDisplayItem(identifier, status); }));
                return;
            } // if

            // change the status of the security base
            if (lvSecurityBases.Items.ContainsKey(identifier) == true)
            {
                lvSecurityBases.Items[identifier].ImageIndex = (int)(status);
            } // if
        }

        private void LoadConfig()
        {
            try
            {
                _accounts.Clear();
                using (StreamReader sr = new StreamReader(Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "Config.cfg")))
                {
                    string line = string.Empty;
                    while ((line = sr.ReadLine()) != null)
                    {
                        string[] fields = line.Split(',');
                        if (fields.Length == 3)
                        {
                            // first line is IP/PORT config
                            tstbIP.Text = fields[0].ToString();
                            tstbUDP.Text = fields[1].ToString();
                            tstbTCP.Text = fields[2].ToString();
                        }
                        else if (fields.Length == 7)
                        {
                            // other lines are accounts
                            if (_accounts != null)
                            {
                                _accounts.Add(fields[0], new Account(fields[0], fields[1], fields[2], fields[3], fields[4], fields[5], Convert.ToUInt32(fields[6])));
                            }
                        }
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }

        private void SaveConfig()
        {
            try
            {
                using (StreamWriter sw = new StreamWriter(Path.Combine(Path.GetDirectoryName(Assembly.GetExecutingAssembly().Location), "Config.cfg")))
                {
                    string line = string.Empty;
                    // save the ip/port info
                    line = tstbIP.Text + ',' + tstbUDP.Text + ',' + tstbTCP.Text;
                    sw.WriteLine(line);
                    // save the account info
                    if (_accounts != null)
                    {
                        foreach (string key in _accounts.Keys)
                        {
                            line = _accounts[key].Identifier + ',' + _accounts[key].IntegrationId + ',' + _accounts[key].IntegrationAccessCode + ',' +
                                _accounts[key].UdpChannelFunction + ',' + _accounts[key].TcpChannelFunction + ',' + _accounts[key].InstallerCode + ',' + _accounts[key].KeyChangeTime.ToString();
                            sw.WriteLine(line);
                        } // foreach
                    }
                }
            }
            catch (Exception ex)
            {
                MessageBox.Show(ex.Message);
            }
        }
        #endregion

        #region Threads
        private void DisplayDebug(string msg)
        {
            if (rtbDebug.InvokeRequired)
            {
                rtbDebug.BeginInvoke(new MethodInvoker(delegate() { DisplayDebug(msg); }));
                return;
            }

            if (rtbDebug.Lines.Count() >= 500)
            {
                rtbDebug.Clear();
            } // if

            rtbDebug.AppendText(msg);

            Log(msg);
        }

        private void DebugOperations(CancellationToken ctoken)
        {
            try
            {
                while (!ctoken.IsCancellationRequested)
                {
                    int count = 0;
                    lock (_msgQueue)
                    {
                        count = _msgQueue.Count;
                    } // lock

                    if (count > 0)
                    {
                        string msg = _msgQueue.ElementAt(0);
                        DisplayDebug(msg);

                        lock (_msgQueue)
                        {
                            _msgQueue.Remove(msg);
                        } // lock
                    } // if                  

                    // if _msgQueue was empty, increase sleep timer to alleviate system usage
                    // until messages to process, then ramp up again
                    Thread.Sleep(((count == 0) ? 10 : 1));
                } // while
            }
            catch (Exception)
            {
                // who knows
            }
            finally
            {
                // cleanup
            } // try

            return;
        }
		#endregion

		private void rtbDebug_TextChanged(object sender, EventArgs e)
		{

		}

		private void tsMain_ItemClicked(object sender, ToolStripItemClickedEventArgs e)
		{

		}

		private void tstbIP_Click(object sender, EventArgs e)
		{

		}
	}

	#region Constants
	public static class Constants
    {
        public const int     SYSTEM_PULSE     = 20; // unit time depends on thread loop's execution interval
        public const int     ACK_TIMEOUT      = 5; // seconds
        public const int     SEND_TIMEOUT     = 5; // seconds
        public const int     RETRY_COUNT      = 4;
        public const int     RX_IDLE_TIME     = 30;
        public const int     TX_IDLE_TIME     = 0;
        public const UInt32  TCP_IDLE_TIMEOUT = 320; // seconds
        public const UInt32  UDP_IDLE_TIMEOUT = 360; // seconds
        public static byte[] APP_LICENSE      = { 0x12, 0xE8, 0x65, 0x9B, 0x92, 0xE9, 0x22, 0x4D, 0xD4, 0x62, 0xEE, 0x75, 0x1B, 0xD1, 0xB0, 0xD5 }; //all 0s here is an invalid license key that must be updated
    }
    #endregion

    #region Enums
    public enum SecurityBaseStatus : byte { Unknown = 0, Connected, Disconnected };
    #endregion

    #region Classes
    public class DebugEventArgs : EventArgs
    {
        public string msg;

        public DebugEventArgs(string message)
        {
            msg = message;
        }
    }

    public class SecurityBaseUpdateEventArgs : EventArgs
    {
        public string             identifier;
        public SecurityBaseStatus status;

        public SecurityBaseUpdateEventArgs(string identifier, SecurityBaseStatus status)
        {
            this.identifier = identifier;
            this.status     = status;
        }
    }

    public class InteractiveServices
    {
        #region Variables
        private bool _flgDisposed = false;
        private InteractiveSDK _sdk;
        private object _securitybaseslock;
        private Dictionary<string, ISecurityBase> _securitybases;
        private DataStore _datastore;
        private object _tcpsessionslock;
        private SortedDictionary<SessionKey, SessionData> _tcpsessions;
        private object _udpsessionslock;
        private SortedDictionary<SessionKey, SessionData> _udpsessions;
        private TCPServer _tcpserver;
        private UDPPoint  _udplistener;
        private IDiagnostics _diagnostics;
        private System.Timers.Timer _timer = null;
        private System.Timers.Timer _tmrDiagnostics = null;
        #endregion

        #region Constructor
        public InteractiveServices()
        {
            _sdk = new InteractiveSDK();
            _securitybaseslock = new object();
            _securitybases = new Dictionary<string, ISecurityBase>();
            _datastore = new DataStore();
            _tcpsessionslock = new object();
            _tcpsessions = new SortedDictionary<SessionKey, SessionData>(new SessionKeyComparer());
            _udpsessionslock = new object();
            _udpsessions = new SortedDictionary<SessionKey, SessionData>(new SessionKeyComparer());
            _tcpserver = new TCPServer();
            _udplistener = new UDPPoint();
            _timer = new System.Timers.Timer();
            _tmrDiagnostics = new System.Timers.Timer();
        }

        ~InteractiveServices()
        {
            Dispose(false);
        }
        #endregion

        #region Properties

        public InteractiveSDK sdk
        {
            get { return (_sdk); }
            set { _sdk = value; }
        }

        public Dictionary<string, ISecurityBase> SecurityBases
        {
            get { return (_securitybases); }
        }

        #endregion

        #region Public Methods

        public void Activate(string ip, int udpport, int tcpport)
        {
            try
            {
                // set the license key
                _sdk.LicenseManager.LicenseKey = Constants.APP_LICENSE;

                // create the diagnostics
                if (null == (_diagnostics = _sdk.CreateDiagnostics()))
                {
                    throw new Exception("diagnostics couldn't be created");
                }

				// start tcp server Protocolo de Control de Transmisión
				ConnectTcpEvents();
                if (_tcpserver.Activate(ip, tcpport) == false)
                {
                    _tcpserver.Shutdown();
                    DisconnectTcpEvents();
                    throw new Exception("tcp server activation failed");
                } // if

                // start udp listener
                ConnectUdpEvents();
                if (_udplistener.Activate(ip, udpport) == false)
                {
                    _udplistener.Shutdown(1000);
                    DisconnectUdpEvents();
                    throw new Exception("udp listener activation failed");
                } // if

                _timer.Elapsed += new ElapsedEventHandler(OnTimedEvent);
                _timer.AutoReset = true;
                _timer.Interval = 500;
                _timer.Enabled = true;

                _tmrDiagnostics.Elapsed += new ElapsedEventHandler(OnDiagnosticsTimerEvent);
                _tmrDiagnostics.AutoReset = true;
                _tmrDiagnostics.Interval = 60000;
                _tmrDiagnostics.Enabled = true;
            }
            catch (InteractiveSdkException)
            {
                throw new Exception("Cannot pre-set the default license data! or Cannot create diagnostics interface!");
            }
            catch (Exception ex)
            {
                throw new Exception("Activate() Failed", ex);
            } // try
        }

        public void Shutdown()
        {
            try
            {
                _timer.Enabled = false;
                _timer.Elapsed -= new ElapsedEventHandler(OnTimedEvent);

                _tmrDiagnostics.Enabled = false;
                _tmrDiagnostics.Elapsed -= new ElapsedEventHandler(OnDiagnosticsTimerEvent);
                _diagnostics.Dispose();

                // shutdown udp listener
                if (_udplistener != null)
                {
                    _udplistener.Shutdown(1000);
                } // if
                DisconnectUdpEvents();

                // shutdown tcp server
                if (_tcpserver != null)
                {
                    _tcpserver.Shutdown();
                } // if
                DisconnectTcpEvents();

                //wait for the shutdown
                while ((false != _udplistener.IsActive()) ||
                    (false != _tcpserver.IsActive()))
                {
                    //take a nap
                    Thread.Sleep(100);
                }

            }
            catch (Exception ex)
            {
                throw new Exception("Shutdown() Failed", ex);
            } // try
        }

        public Dictionary<string, Account> GetAccounts()
        {
            return (new Dictionary<string, Account>(_datastore.Accounts));
        }

        public bool AddAccount(Account account)
        {
            return (_datastore.AddAccount(account.Identifier, account.IntegrationId, account.IntegrationAccessCode, 
                account.UdpChannelFunction, account.TcpChannelFunction, account.InstallerCode, account.KeyChangeTime));
        }

        public bool RemoveAccount(string id)
        {
            return (_datastore.RemoveAccount(id));
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }

        #endregion

        #region Private Methods

        private void ConnectTcpEvents()
        {
            if (_tcpserver != null)
            {
                _tcpserver.ActivateEvent += new EventHandler<SocketEventArgs>(_tcpserver_ActivateEvent);
                _tcpserver.ShutdownEvent += new EventHandler<SocketEventArgs>(_tcpserver_ShutdownEvent);
                _tcpserver.MainLoopEvent += new EventHandler<SocketEventArgs>(_tcpserver_MainLoopEvent);
                _tcpserver.ConnectionOpenEvent += new EventHandler<SocketEventArgs>(_tcpserver_ConnectionOpenEvent);
                _tcpserver.ConnectionClosedEvent += new EventHandler<SocketEventArgs>(_tcpserver_ConnectionClosedEvent);
                _tcpserver.ConnectionThreadEvent += new EventHandler<SocketEventArgs>(_tcpserver_ConnectionThreadEvent);
                _tcpserver.ConnectionRxDataEvent += new EventHandler<SocketEventArgs>(_tcpserver_ConnectionRxDataEvent);
                _tcpserver.ConnectionRxIdleEvent += new EventHandler<SocketEventArgs>(_tcpserver_ConnectionRxIdleEvent);
                _tcpserver.ConnectionTxIdleEvent += new EventHandler<SocketEventArgs>(_tcpserver_ConnectionTxIdleEvent);
                _tcpserver.ExceptionEvent += new EventHandler<ExceptionEventArgs>(_tcpserver_ExceptionEvent);
            } // if
        }

        private void DisconnectTcpEvents()
        {
            if (_tcpserver != null)
            {
                _tcpserver.ActivateEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ActivateEvent);
                _tcpserver.ShutdownEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ShutdownEvent);
                _tcpserver.MainLoopEvent -= new EventHandler<SocketEventArgs>(_tcpserver_MainLoopEvent);
                _tcpserver.ConnectionOpenEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ConnectionOpenEvent);
                _tcpserver.ConnectionClosedEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ConnectionClosedEvent);
                _tcpserver.ConnectionRxDataEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ConnectionRxDataEvent);
                _tcpserver.ConnectionRxIdleEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ConnectionRxIdleEvent);
                _tcpserver.ConnectionTxIdleEvent -= new EventHandler<SocketEventArgs>(_tcpserver_ConnectionTxIdleEvent);
                _tcpserver.ExceptionEvent -= new EventHandler<ExceptionEventArgs>(_tcpserver_ExceptionEvent);
            } // if
        }

        private void ConnectUdpEvents()
        {
            if (_udplistener != null)
            {
                _udplistener.ActivateEvent += new EventHandler<SocketEventArgs>(_udplistener_ActivateEvent);
                _udplistener.ShutdownEvent += new EventHandler<SocketEventArgs>(_udplistener_ShutdownEvent);
                _udplistener.MainLoopEvent += new EventHandler<SocketEventArgs>(_udplistener_MainLoopEvent);
                _udplistener.ReceivedEvent += new EventHandler<SocketEventArgs>(_udplistener_ReceivedEvent);
                _udplistener.ReadIdleEvent += new EventHandler<SocketEventArgs>(_udplistener_ReadIdleEvent);
                _udplistener.SendIdleEvent += new EventHandler<SocketEventArgs>(_udplistener_SendIdleEvent);
                _udplistener.ExceptionEvent += new EventHandler<ExceptionEventArgs>(_udplistener_ExceptionEvent);
            } // if
        }

        private void DisconnectUdpEvents()
        {
            if (_udplistener != null)
            {
                _udplistener.ActivateEvent -= new EventHandler<SocketEventArgs>(_udplistener_ActivateEvent);
                _udplistener.ShutdownEvent -= new EventHandler<SocketEventArgs>(_udplistener_ShutdownEvent);
                _udplistener.MainLoopEvent -= new EventHandler<SocketEventArgs>(_udplistener_MainLoopEvent);
                _udplistener.ReceivedEvent -= new EventHandler<SocketEventArgs>(_udplistener_ReceivedEvent);
                _udplistener.ReadIdleEvent -= new EventHandler<SocketEventArgs>(_udplistener_ReadIdleEvent);
                _udplistener.SendIdleEvent -= new EventHandler<SocketEventArgs>(_udplistener_SendIdleEvent);
                _udplistener.ExceptionEvent -= new EventHandler<ExceptionEventArgs>(_udplistener_ExceptionEvent);
            } // if
        }

        private void ConnectChannelEvents(IChannel channel)
        {
            if (channel != null)
            {
                channel.DataProcessingEvent += new ChannelProprietaryDataEventHandler(channel_DataProcessingEvent);
                channel.ErrorNotificationEvent += new ChannelErrorNotificationEventHandler(channel_ErrorNotificationEvent);
                channel.EventNotificationEvent += new ChannelEventNotificationEventHandler(channel_EventNotificationEvent);
                channel.InspectPayloadEvent += new ChannelRawDataByteArrayEventHandler(channel_InspectPayloadEvent);
                channel.PacketReceivedEvent += new ChannelRawDataByteArrayEventHandler(channel_PacketReceivedEvent);
                channel.SendDataPacketEvent += new ChannelRawDataByteArrayEventHandler(channel_SendDataPacketEvent);
                channel.StateNotificationEvent += new ChannelStateNotificationEventHandler(channel_StateNotificationEvent);
            } // if
        }

        private void DisconnectChannelEvents(IChannel channel)
        {
            if (channel != null)
            {
                channel.DataProcessingEvent -= new ChannelProprietaryDataEventHandler(channel_DataProcessingEvent);
                channel.ErrorNotificationEvent -= new ChannelErrorNotificationEventHandler(channel_ErrorNotificationEvent);
                channel.EventNotificationEvent -= new ChannelEventNotificationEventHandler(channel_EventNotificationEvent);
                channel.InspectPayloadEvent -= new ChannelRawDataByteArrayEventHandler(channel_InspectPayloadEvent);
                channel.PacketReceivedEvent -= new ChannelRawDataByteArrayEventHandler(channel_PacketReceivedEvent);
                channel.SendDataPacketEvent -= new ChannelRawDataByteArrayEventHandler(channel_SendDataPacketEvent);
                channel.StateNotificationEvent -= new ChannelStateNotificationEventHandler(channel_StateNotificationEvent);
            } // if
        }

        private void ConnectSecurityEvents(ISecurityBase securitybase)
        {
            if (securitybase != null)
            {
                securitybase.DataUpdateNotificationExtEvent += new SecurityDataUpdateNotificationExtEventHandler(_security_DataUpdateNotificationEvent);
                securitybase.GeneralNotificationEvent += new SecurityGeneralNotificationEventHandler(_security_GeneralNotificationEvent);
            } // if
        }

        private void DisconnectSecurityEvents(ISecurityBase securitybase)
        {
            if (securitybase != null)
            {
                securitybase.DataUpdateNotificationExtEvent -= new SecurityDataUpdateNotificationExtEventHandler(_security_DataUpdateNotificationEvent);
                securitybase.GeneralNotificationEvent -= new SecurityGeneralNotificationEventHandler(_security_GeneralNotificationEvent);
            } // if
        }

        private bool WriteDataToChannel(IChannel channel, byte[] data)
        {
            // push the received data into the channel for processing
            if (channel != null)
            {
                try
                {
                    if (channel.ReceiveRawData(data) != data.Length)
                    {
                        OnDebugEvent(this, new DebugEventArgs("[WriteDataToChannel]: Not all data was written!\r\n"));
                    }
                    else
                    {
                        return (true);
                    } // if
                }
                catch (InteractiveSdkException)
                {
                    OnDebugEvent(this, new DebugEventArgs("[WriteDataToChannel]: Channel failed to receive data!\r\n"));
                }
                catch { throw; }
            } // if
            return (false);
        }

        private bool SetChannelProperties(IChannel channel, string connectioninfo, SessionKey key)
        {
            if (channel == null)
            {
                return (false);
            } // if

            // store connection type (UDP or TCP)
            channel.ConnectionInfo = connectioninfo;
            // hook up database
            channel.DataStore = _datastore;
            // create & set block ciper
            IBlockCipher cipher = _sdk.CreateBlockCipher(CipherType.ITV2_AES128);
            if (cipher == null)
            {
                OnDebugEvent(this, new DebugEventArgs("[SetChannelProperties]: Block cipher creation failed!\r\n"));
                return (false);
            } // if
            try
            {
                channel.SetBlockCipher(CipherType.ITV2_AES128, cipher);
            }
            catch (InteractiveSdkException)
            {
                OnDebugEvent(this, new DebugEventArgs("[SetChannelProperties]: Failed to set the block cipher reference!\r\n"));
                return (false);
            } // if
            // setup timings
            channel.TxRetryDelay = Constants.ACK_TIMEOUT;
            channel.TxRetryCount = Constants.RETRY_COUNT;
            channel.RxIdleTimeout = Constants.RX_IDLE_TIME;
            channel.TxIdleTimeout = Constants.TX_IDLE_TIME;
            channel.Tag = key;
            return (true);
        }

        private UInt16 GetUInt16(byte[] data, int index)
        {
            UInt16 retval = BitConverter.ToUInt16(data, index);

            if (BitConverter.IsLittleEndian == true)
            {
                byte[] reverse = BitConverter.GetBytes(retval);
                Array.Reverse(reverse);
                retval = BitConverter.ToUInt16(reverse, 0);
            } // if

            return (retval);
        }

        private void ProcessInternalStates()
        {
            lock(_securitybaseslock)
            {
		        int count = _securitybases.Count();
		        for (int i = 0; i < count; ++i)
		        {
                    KeyValuePair<string, ISecurityBase> kvp = _securitybases.ElementAt(i);
                    ISecurityBase securitybase = kvp.Value;
                    securitybase.ProcessState();
		        }
            }
        }

        private bool ProcSessionTimeout(SessionData clsSession)
        {
	        //check session idle timeout
	        if (false != clsSession.TestIdleTime())
	        {
		        //the session has timed out
		        return true;
	        }
	        else if (false != clsSession.TestSysTicks())
	        {
		        //reset the time
                clsSession.SysTicks = Constants.SYSTEM_PULSE;

		        //get channel
                IChannel channel = clsSession.Channel;
		        if (null != channel)
		        {
			        //pulse the channel
                    try
                    {
                        channel.ProcessState();
                    }
                    catch
                    {
                        OnDebugEvent(this, new DebugEventArgs("[ProcSessionTimeout] Failed to pulse the channel!\n"));
                    }
		        }
	        }
	        //the session has not timed out
	        return false;
        }

        private void Dispose(bool flgDisposing)
        {
            //check if the object has already been disposed of
            if (_flgDisposed) return;

            //explicit disposing?
            if (flgDisposing)
            {
                //dispose of the managed resources
            }

            //dispose of the unmanaged resources

            //the object has been disposed of
            _flgDisposed = true;
        }

        #region Diagnostics
        void CheckDiagnostics()
        {
            if (null == _diagnostics)
            {
                return;
            }

            string diagnostics_string = string.Empty;

            diagnostics_string += "CheckDiagnostics\n";
            diagnostics_string += "---------------------------------------------------------------------------\n";

            diagnostics_string += GetTypeInfo(ObjectType.Interactive);
            diagnostics_string += GetTypeInfo(ObjectType.BlockCipher);
            diagnostics_string += GetTypeInfo(ObjectType.AccessCode);
            diagnostics_string += GetTypeInfo(ObjectType.AccessCodeAttributes);
            diagnostics_string += GetTypeInfo(ObjectType.AccessCodeManager);
            diagnostics_string += GetTypeInfo(ObjectType.AccessCredentials);
            diagnostics_string += GetTypeInfo(ObjectType.AlarmTypeContainer);
            diagnostics_string += GetTypeInfo(ObjectType.AssignmentData);
            diagnostics_string += GetTypeInfo(ObjectType.AssignmentList);
            diagnostics_string += GetTypeInfo(ObjectType.BuzzerDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.CommandOutputDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.EventBufferEntryDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.KeyPressedDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.LCDCursorDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.LCDUpdateDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.LEDStatusDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.LifeStyleSettings);
            diagnostics_string += GetTypeInfo(ObjectType.Partition);
            diagnostics_string += GetTypeInfo(ObjectType.PartitionManager);
            diagnostics_string += GetTypeInfo(ObjectType.PartitionStateData);
            diagnostics_string += GetTypeInfo(ObjectType.ProgrammingDataContainer);
            diagnostics_string += GetTypeInfo(ObjectType.Repository);
            diagnostics_string += GetTypeInfo(ObjectType.RequestResult);
            diagnostics_string += GetTypeInfo(ObjectType.SecurityBase);
            diagnostics_string += GetTypeInfo(ObjectType.SecurityEventSink);
            diagnostics_string += GetTypeInfo(ObjectType.SpecificFunctions);
            diagnostics_string += GetTypeInfo(ObjectType.SystemCapabilities);
            diagnostics_string += GetTypeInfo(ObjectType.SystemInformation);
            diagnostics_string += GetTypeInfo(ObjectType.SystemManager);
            diagnostics_string += GetTypeInfo(ObjectType.TroubleData);
            diagnostics_string += GetTypeInfo(ObjectType.TroubleList);
            diagnostics_string += GetTypeInfo(ObjectType.VirtualKeypad);
            diagnostics_string += GetTypeInfo(ObjectType.VirtualKeypadManager);
            diagnostics_string += GetTypeInfo(ObjectType.VirtualZone);
            diagnostics_string += GetTypeInfo(ObjectType.VirtualZoneManager);
            diagnostics_string += GetTypeInfo(ObjectType.VirtualZoneStatus);
            diagnostics_string += GetTypeInfo(ObjectType.Zone);
            diagnostics_string += GetTypeInfo(ObjectType.ZoneAttributes);
            diagnostics_string += GetTypeInfo(ObjectType.ZoneManager);

            diagnostics_string += "---------------------------------------------------------------------------\n";

            OnDebugEvent(this, new DebugEventArgs(diagnostics_string));
        }

        string GetTypeInfo(ObjectType type)
        {
            string retval = string.Empty;
            UInt32 mem_count = 0;
            UInt32 ref_count = 0;
            try
            {
                _diagnostics.GetObjectTypeCounts(type, out mem_count, out ref_count);
                if ((0 < mem_count) || (0 < ref_count))
                {
                    retval = string.Format("{0} -> Mem Count: {1}, Ref Count: {2}\n", Enum.GetName(typeof(ObjectType), type), mem_count, ref_count);
                }
            }
            catch (InteractiveSdkException e)
            {
                retval = string.Format("Error getting {0} information [SDK Exception = {1}]\n", Enum.GetName(typeof(ObjectType), type), e.SdkDescription);
            }
            catch (Exception ex)
            {
            }
            return (retval);
        }

        #endregion

        #endregion

        #region Private Events
        private void OnTimedEvent(Object source, System.Timers.ElapsedEventArgs e)
        {
            if (_securitybases != null)
            {
                lock (_securitybaseslock)
                {
                    for (int i = 0, max = _securitybases.Count; i < max; ++i)
                    {
                        if (true == _securitybases.ElementAt(i).Value.ReadyToUse)
                        {
                            OnSecurityBaseUpdateEvent(this, new SecurityBaseUpdateEventArgs(_securitybases.ElementAt(i).Key, SecurityBaseStatus.Connected));
                        }
                        else
                        {
                            OnSecurityBaseUpdateEvent(this, new SecurityBaseUpdateEventArgs(_securitybases.ElementAt(i).Key, SecurityBaseStatus.Disconnected));
                        }
                    }
                }
            }
        }

        private void OnDiagnosticsTimerEvent(Object source, System.Timers.ElapsedEventArgs e)
        {
            if (_diagnostics != null)
            {
                CheckDiagnostics();
            }
        }
        #endregion

        #region InteractiveServices Events
        public event EventHandler<DebugEventArgs>              DebugEvent;
        public event EventHandler<ExceptionEventArgs>          ExceptionEvent;
        public event EventHandler<SecurityBaseUpdateEventArgs> SecurityBaseUpdateEvent;

        public void OnDebugEvent(object sender, DebugEventArgs e)
        {
            // Make a temporary copy of the event to avoid possibility of
            // a race condition if the last subscriber unsubscribes
            // immediately after the null check and before the event is raised.
            EventHandler<DebugEventArgs> handler = DebugEvent;
            if (handler != null)
            {
                handler(sender, e);
            } // if
        }

        public void OnExceptionEvent(object sender, ExceptionEventArgs e)
        {
            // Make a temporary copy of the event to avoid possibility of
            // a race condition if the last subscriber unsubscribes
            // immediately after the null check and before the event is raised.
            EventHandler<ExceptionEventArgs> handler = ExceptionEvent;
            if (handler != null)
            {
                handler(sender, e);
            } // if
        }

        public void OnSecurityBaseUpdateEvent(object sender, SecurityBaseUpdateEventArgs e)
        {
            // Make a temporary copy of the event to avoid possibility of
            // a race condition if the last subscriber unsubscribes
            // immediately after the null check and before the event is raised.
            EventHandler<SecurityBaseUpdateEventArgs> handler = SecurityBaseUpdateEvent;
            if (handler != null)
            {
                handler(sender, e);
            } // if
        }
        #endregion

        #region TCPServer Events
        private void _tcpserver_ActivateEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Activate Event]\r\n"));
        }

        private void _tcpserver_ShutdownEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Shutdown Event]\r\n"));
        }

        private void _tcpserver_MainLoopEvent(object sender, SocketEventArgs e)
        {
            ProcessInternalStates();
        }

        private void _tcpserver_ConnectionTxIdleEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Connection Tx Idle Event]\r\n"));
        }

        private void _tcpserver_ConnectionRxIdleEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Connection Rx Idle Event]\r\n"));
        }

        private void _tcpserver_ConnectionRxDataEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Connection Rx Data Event]\r\n"));

            if (sender == null)
            {
                return;
            } // if

            SessionKey key = new SessionKey(SessionTypes.TCP, e.remoteaddress);
            IChannel channel = null;
            lock (_tcpsessionslock)
            {
                if (_tcpsessions.ContainsKey(key) == true)
                {
                    channel = _tcpsessions[key].Channel;
                    if (channel == null)
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionRxDataEvent]: Missing required channel!\r\n"));
                    } // if
                    _tcpsessions[key].IdleTime = Constants.TCP_IDLE_TIMEOUT;
                }
                else
                {
                    OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionRxDataEvent]: Missing required session info!\r\n"));
                } // if
            } // lock

            // push data into channel
            if (WriteDataToChannel(channel, e.databuffer) == false)
            {
                OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionRxDataEvent] Failed to write data to channel!\r\n"));
            } // if
        }

        private void _tcpserver_ConnectionClosedEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Connection Closed Event]\r\n"));

            SessionKey key = new SessionKey(SessionTypes.TCP, e.remoteaddress);
            lock (_tcpsessionslock)
            {
                // check if session is present
                if (_tcpsessions.ContainsKey(key) == true)
                {
                    TCPProxy tcp = _tcpsessions[key].TCPProxy;
                    if ((sender as TCPProxy) == tcp)
                    {
                        _tcpsessions[key].TCPProxy = null;
                        IChannel channel = _tcpsessions[key].Channel;
                        if (channel != null)
                        {
                            try
                            {
                                channel.CloseChannel();
                            }
                            catch (InteractiveSdkException)
                            {
                                OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionClosedEvent]: Cannot close the channel!\r\n"));
                            } // try
                        }
                        else
                        {
                            OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionClosedEvent]: There is no channel associated with the session!\r\n"));
                            _tcpsessions.Remove(key);
                        } // if
                    } // if
                } // if
            } // lock
        }

        private void _tcpserver_ConnectionThreadEvent(object sender, SocketEventArgs e)
        {
            //OnDebugEvent(sender, new DebugEventArgs("[TCP Connection Thread Event]\n"));

	        //create session key
            SessionKey key = new SessionKey(SessionTypes.TCP, e.remoteaddress);
	        //process session
	        lock(_tcpsessionslock)
            {
		        //find session
                // check if session is present
                if (_tcpsessions.ContainsKey(key) == true)
                {
                    SessionData session = _tcpsessions[key];
                    if (false != ProcSessionTimeout(session))
                    {
                        //the session has timed out
                        OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionThreadEvent] The session has timed out!\n"));

                        //prepare for closing the channel
                        IChannel channel = session.Channel;
                        if (null != channel)
                        {
                            //close the channel (it should remove the session)
                            try
                            {
                                channel.CloseChannel();
                            }
                            catch
                            {
                                OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionThreadEvent] Cannot close the channel!\n"));
                            }
                        }
                        else
                        {
                            //missing channel
                            OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionThreadEvent] There is no channel associated with the session!\n"));

                            //remove the session
                            _tcpsessions.Remove(key);
                        }
                    }
                }
            }
        }

        private void _tcpserver_ConnectionOpenEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[TCP Connection Open Event]\r\n"));

            if (sender == null)
            {
                return;
            } // if

            // create session key
            SessionKey key = new SessionKey(SessionTypes.TCP, e.remoteaddress);
            IChannel channel = null;
            lock (_tcpsessionslock)
            {
                // check if session is present
                if (_tcpsessions.ContainsKey(key) == true)
                {
                    OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Found existing session!\r\n"));
                    channel = _tcpsessions[key].Channel;
                    if (channel != null)
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Replacing proxy!\r\n"));
                        TCPProxy tcp = _tcpsessions[key].TCPProxy;
                        _tcpsessions[key].TCPProxy = (sender as TCPProxy);
                        if (tcp != null)
                        {
                            _tcpserver.ShutProxy(tcp);
                        } // if
                        _tcpsessions[key].IdleTime = Constants.TCP_IDLE_TIMEOUT;
                    }
                    else
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Failed to get the channel!\r\n"));
                        _tcpsessions.Remove(key);
                    } // if
                } // if

                if (channel == null)
                {
                    // create new session
                    SessionData data = new SessionData();
                    data.PeerAddress = e.remoteaddress;
                    data.TCPProxy = (sender as TCPProxy);
                    data.SysTicks = Constants.SYSTEM_PULSE;
                    data.IdleTime = Constants.TCP_IDLE_TIMEOUT;

                    // create new channel
                    if ((channel = _sdk.CreateChannel(TSP.DSC_InteractiveSDK.ProtocolType.ITV2)) != null)
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: New channel has been created!\r\n"));
                        if (SetChannelProperties(channel, ExtendedParameterValues.ITV2_Param_Value_TCP.ToString(), key) == true)
                        {
                            OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: New channel's properties have been set\r\n"));
                            try
                            {
                                data.Channel = channel;
                                _tcpsessions.Add(key, data);
                                ConnectChannelEvents(channel);
                                OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: New session has been added to the list\r\n"));
                            }
                            catch
                            {
                                OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Failed to add new session info to the list\r\n"));
                                channel.Tag = null;
                                try
                                {
                                    channel.CloseChannel();
                                }
                                catch (InteractiveSdkException)
                                {
                                    OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Cannot close the channel!\r\n"));
                                } // try
                                channel = null;
                            } // try
                        }
                        else
                        {
                            OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Failed to set the channel's properties\r\n"));
                            channel = null;
                        } // if
                    }
                    else
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Failed to create the channel\r\n"));
                    } // if
                } // if
            } // lock

            if (channel == null)
            {
                OnDebugEvent(sender, new DebugEventArgs("[_tcpserver_ConnectionOpenEvent]: Failure\r\n"));
                try { (sender as TCPProxy).Shutdown(0); } catch { };
            } // if
        }

        private void _tcpserver_ExceptionEvent(object sender, ExceptionEventArgs e)
        {
            OnExceptionEvent(sender, e);
        }
        #endregion

        #region UDPPoint Events
        private void _udplistener_ActivateEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[UDP Activate Event]\r\n"));
        }

        private void _udplistener_ShutdownEvent(object sender, SocketEventArgs e)
        {
            OnDebugEvent(sender, new DebugEventArgs("[UDP Shutdown Event]\r\n"));

            // close all UDP sessions and channels
            lock (_udpsessionslock)
            {
                List<SessionKey> keys = new List<SessionKey>(_udpsessions.Keys);
                int count = _udpsessions.Keys.Count;
                for (int i = 0; i < count; ++i)
                {
                    SessionData session = _udpsessions[keys[i]];
                    IChannel channel = session.Channel;
                    if (channel != null)
                    {
                        try
                        {
                            channel.CloseChannel();
                        }
                        catch (InteractiveSdkException)
                        {
                            OnDebugEvent(sender, new DebugEventArgs("[UDP Shutdown Event]: Cannot close the channel!\r\n"));
                        } // try
                    }
                    else
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[UDP Shutdown Event]: There is no channel associated with the session!\r\n"));
                        _udpsessions.Remove(keys[i]);
                    } // if
                } // for
            } // lock
        }

        private void _udplistener_MainLoopEvent(object sender, SocketEventArgs e)
        {
            lock (_udpsessionslock)
            {
		        //process all sessions
		        for (int i = _udpsessions.Count(); 0 < i; --i)
		        {
			        //get the sessions one by one
                    KeyValuePair<SessionKey, SessionData> kvp = _udpsessions.ElementAt(i - 1);
                    SessionData session = kvp.Value;

			        //process session timeouts
			        if (false != ProcSessionTimeout(session))
			        {
				        //the session has timed out
                        OnDebugEvent(sender, new DebugEventArgs("[_udplistener_MainLoopEvent] The session has timed out!\n"));

				        //prepare for closing the channel
				        IChannel channel = session.Channel;
				        if (null != channel)
				        {
					        //close the channel (it should remove the session)
                            try
                            {
                                channel.CloseChannel();
                            }
                            catch
                            {
                                OnDebugEvent(sender, new DebugEventArgs("[_udplistener_MainLoopEvent] Cannot close the channel!\n"));
                            }
				        }
				        else
				        {
					        //missing channel
                            OnDebugEvent(sender, new DebugEventArgs("[_udplistener_MainLoopEvent] There is no channel associated with the session!\n"));

					        //remove the session
                            _udpsessions.Remove(kvp.Key);
				        }
			        }
		        }
            }
            //pulse security base
	        ProcessInternalStates();
        }

        private void _udplistener_SendIdleEvent(object sender, SocketEventArgs e)
        {
            //OnDebugEvent(sender, new DebugEventArgs("[UDP Tx Idle Event]\r\n"));
        }

        private void _udplistener_ReadIdleEvent(object sender, SocketEventArgs e)
        {
            //OnDebugEvent(sender, new DebugEventArgs("[UDP Rx Idle Event]\r\n"));
        }

        private void _udplistener_ReceivedEvent(object sender, SocketEventArgs e)
        {
            //OnDebugEvent(sender, new DebugEventArgs("[UDP Received Event]\r\n"));

            if ((sender == null) || (e == null))
            {
                return;
            } // if

            // create session key
            SessionKey key = new SessionKey(SessionTypes.UDP, e.remoteaddress);
            IChannel channel = null;
            lock (_udpsessionslock)
            {
                // check if session is present
                if (_udpsessions.ContainsKey(key) == true)
                {
                    SessionData session = _udpsessions[key];

                    if ((channel = session.Channel) != null)
                    {
                        session.IdleTime = Constants.UDP_IDLE_TIMEOUT;
                    }
                    else
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: Failed to get the channel!\r\n"));
                        _udpsessions.Remove(key);
                    } // if
                } // if

                if (channel == null)
                {
                    // create new session
                    SessionData data = new SessionData();
                    data.PeerAddress = key.peeraddress;
                    data.UDPPoint = (sender as UDPPoint);
                    data.SysTicks = Constants.SYSTEM_PULSE;
                    data.IdleTime = Constants.UDP_IDLE_TIMEOUT;

                    // create new channel
                    if ((channel = _sdk.CreateChannel(TSP.DSC_InteractiveSDK.ProtocolType.ITV2)) != null)
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[UDP _udplistener_ReceivedEvent Event]: New channel has been created!\r\n"));
                        if (SetChannelProperties(channel, ExtendedParameterValues.ITV2_Param_Value_UDP.ToString(), key) == true)
                        {
                            OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: New channel's properties have been set!\r\n"));
                            try
                            {
                                data.Channel = channel;
                                _udpsessions.Add(key, data);
                                ConnectChannelEvents(channel);
                                OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: New session has been added to the list!\r\n"));
                            }
                            catch
                            {
                                OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: Failed to add new session info to the list!\r\n"));
                                channel.Tag = null;
                                try
                                {
                                    channel.CloseChannel();
                                }
                                catch (InteractiveSdkException)
                                {
                                    OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: Cannot close the channel!\r\n"));
                                } // try
                                channel = null;
                            } // try
                        }
                        else
                        {
                            OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: Failed to set the channel's properties!\r\n"));
                            channel = null;
                        } // if
                    }
                    else
                    {
                        OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent]: Failed to create the channel!\r\n"));
                    } // if
                } // if
            } // lock

            // push data into channel
            if (WriteDataToChannel(channel, e.databuffer) == false)
            {
                OnDebugEvent(sender, new DebugEventArgs("[_udplistener_ReceivedEvent] Failed to write data to channel!\r\n"));
            } // if
        }

        private void _udplistener_ExceptionEvent(object sender, ExceptionEventArgs e)
        {
            OnExceptionEvent(sender, e);
        }
        #endregion

        #region Security Events
        private void _security_GeneralNotificationEvent(ISecurityBase ptrSender, SecurityEventCategory flgEventCategory, SecurityEventType flgEventType, IDataContainer clsDataContainer)
        {
            // process the general notification
            OnDebugEvent(ptrSender, new DebugEventArgs("[Security General Notification] Category: " + Enum.GetName(typeof(SecurityEventCategory), flgEventCategory).ToString() +
                " Type: " + Enum.GetName(typeof(SecurityEventType), flgEventType).ToString() + "\r\n"));

            IRepository repository = ptrSender.Repository;
            OnDebugEvent(ptrSender, new DebugEventArgs("PeerIdentifier = " + repository.PeerIdentifier.ToString() + "\r\n"));
            repository.Dispose();

            // sanity check
            if (clsDataContainer == null)
            {
                return;
            } // if

            if (clsDataContainer.ContainerType == DataContainer.Unknown)
            {
                // do cleanup
                if (clsDataContainer != null)
                {
                    clsDataContainer.Dispose();
                }
                return;
            } // if

            switch (flgEventCategory)
            {
                case SecurityEventCategory.Programming:
                    {
                        IProgrammingDataContainer container = (clsDataContainer as IProgrammingDataContainer);
                        if (container != null)
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("Source: " + Enum.GetName(typeof(ProgrammingSource), container.Source).ToString() + " Mode: " +
                                Enum.GetName(typeof(ProgrammingMode), container.Mode).ToString() + " State: " + Enum.GetName(typeof(ProgrammingState), container.State).ToString() + "\r\n"));
                        } // if
                    }
                    break;
                case SecurityEventCategory.SystemState:
                    {
                        switch (flgEventType)
                        {
                            case SecurityEventType.TimeDate:
                                {
                                    ITextString container = (clsDataContainer as ITextString);
                                    OnDebugEvent(ptrSender, new DebugEventArgs(container.Text.ToString() + "\r\n"));
                                }
                                break;
                            case SecurityEventType.Assignment:
                                {
                                    IAssignmentList container = (clsDataContainer as IAssignmentList);
                                    bool flgDone = false;
                                    for(int i = 0; i < container.Assignments.Length; i++)
                                    {
                                        IAssignmentData assignment = container.Assignments[i];
                                        string info = string.Empty;
                                        string type = string.Empty;
                                        switch (assignment.Type)
                                        {
                                            case AssignmentType.Partition:
                                                {
                                                    type = "Partition(s) Assignment Update\r\n";
                                                    info = string.Format("Partition {0} {1} {2} System\r\n", assignment.PartitionNumber.ToString(),
                                                        Enum.GetName(typeof(AssignmentState), assignment.State).ToString(),
                                                        ((assignment.State == AssignmentState.Assigned) ? "To" : "From"));
                                                }
                                                break;
                                            case AssignmentType.VirtualZone_Zone:
                                                {
                                                    type = "VirtualZone(s) Assignment Update\r\n";
                                                    info = string.Format("VirtualZone {0} {1} {2} Zone {3}\r\n", assignment.VirtualZoneNumber.ToString(), 
                                                        Enum.GetName(typeof(AssignmentState), assignment.State).ToString(), 
                                                        ((assignment.State == AssignmentState.Assigned) ? "To" : "From"), 
                                                        assignment.ZoneNumber.ToString());
                                                }
                                                break;
                                            case AssignmentType.Zone_Partition:
                                                {
                                                    type = "Zone(s) Assignment Update\r\n";
                                                    info = string.Format("Zone {0} {1} {2} Partition {3}\r\n", assignment.ZoneNumber.ToString(),
                                                        Enum.GetName(typeof(AssignmentState), assignment.State).ToString(),
                                                        ((assignment.State == AssignmentState.Assigned) ? "To" : "From"),
                                                        assignment.PartitionNumber.ToString());
                                                }
                                                break;
                                            default:
                                                {
                                                    OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Assignment Type\r\n"));
                                                }
                                                break;
                                        }
                                        if (false == flgDone)
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs(type));
                                            flgDone = true;
                                        }
                                        OnDebugEvent(ptrSender, new DebugEventArgs(info));
                                    }
                                }
                                break;
                            default:
                                {
                                    OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Event Type\r\n"));
                                }
                                break;
                        }
                    }
                    break;
                case SecurityEventCategory.CommandOutput:
                    {
                        ICommandOutputDataContainer container = (clsDataContainer as ICommandOutputDataContainer);
                        if(container != null)
                        {
                            string partitions = string.Empty;
                            for(int i = 0; i < container.Partitions.Length; ++i)
                            {
                                partitions += container.Partitions[i].ToString();
                            }
                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition(s) " + partitions + " Command Output " + container.OutputNumber.ToString() + " State = " + Enum.GetName(typeof(CommandOutputReportingState), container.OutputState).ToString() + "\r\n"));
                        }
                    }
                    break;
                case SecurityEventCategory.EventBuffer:
                    {
                        IEventBufferEntryDataContainer container = (clsDataContainer as IEventBufferEntryDataContainer);
                        OnDebugEvent(ptrSender, new DebugEventArgs("Event Buffer Notification From Partition " + container.Partition.ToString() +
                            " EventType = " + container.EventType.ToString("X2") + " EventCode = " + container.EventCode.ToString("X4") + "\r\n"));
                    }
                    break;
                case SecurityEventCategory.DeviceModule:
                    {
                        switch (flgEventType)
                        {
                            case SecurityEventType.Trouble:
                                {
                                    OnDebugEvent(ptrSender, new DebugEventArgs("Device/Module Trouble(s):\r\n"));
                                    ITroubleList container = (clsDataContainer as ITroubleList);
                                    for (int i = 0, count = container.Troubles.Length; i < count; ++i)
                                    {
                                        OnDebugEvent(ptrSender, new DebugEventArgs(
                                            "DeviceModuleType = " + Enum.GetName(typeof(DeviceModuleType), container.Troubles[i].DeviceModuleType).ToString() + "\r\n" +
                                            "TroubleType = " + Enum.GetName(typeof(TroubleType), container.Troubles[i].TroubleType).ToString() + "\r\n" +
                                            "DeviceModuleNumber = " + container.Troubles[i].DeviceModuleNumber.ToString() + "\r\n" +
                                            "TroubleStatus = " + Enum.GetName(typeof(TroubleState), container.Troubles[i].TroubleStatus).ToString() + "\r\n"));
                                    }
                                }
                                break;
                            default:
                                {
                                    OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Event Type\r\n"));
                                }
                                break;
                        }
                    }
                    break;
                case SecurityEventCategory.Unknown:
                default:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Event Category\r\n"));
                    }
                    break;
            } // switch

            // do cleanup
            if (clsDataContainer != null)
            {
                clsDataContainer.Dispose();
            }
        }

        private void _security_DataUpdateNotificationEvent(ISecurityBase ptrSender, IDataContainer clsDataContainer, SecurityDataSelector[] tblDataSelectors, IDataContainer clsAuxDataContainer)
        {
            // process the data update notification
            OnDebugEvent(ptrSender, new DebugEventArgs("[Security Data Update Notification]\r\n"));

            // sanity check
            if ((clsDataContainer == null) || (tblDataSelectors == null))
            {
                // do cleanup
                if (clsDataContainer != null)
                {
                    clsDataContainer.Dispose();
                }
                if (clsAuxDataContainer != null)
                {
                    clsAuxDataContainer.Dispose();
                }
                return;
            } // if

            if ((clsDataContainer.ContainerType == DataContainer.Unknown) || (tblDataSelectors.Length == 0))
            {
                // do cleanup
                if (clsDataContainer != null)
                {
                    clsDataContainer.Dispose();
                }
                if (clsAuxDataContainer != null)
                {
                    clsAuxDataContainer.Dispose();
                }
                return;
            } // if

            // show the updates info
            switch (clsDataContainer.ContainerType)
            {
                case DataContainer.AccessCode:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode Notification:\r\n"));
                        IAccessCode container = (clsDataContainer as IAccessCode);
                        if (container != null)
                        {
                            UInt32 num_accesscode = container.SystemIndex;
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.SystemIndex:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode System Index = " + container.SystemIndex.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Label:
                                        {
                                            // the panel is appends a "\0" null char at the end of the string. And there may be some garbage bytes after the NULL.
                                            string aLabel = container.Label.ToString();
                                            if(false != aLabel.Contains("\0"))
                                            {
                                                aLabel = aLabel.Substring(0, aLabel.IndexOf("\0"));
                                            }
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Label = " + aLabel + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Value:
                                        {
                                            string aValue = container.Value.ToString();
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Value = " + aValue + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Length:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Length = " + container.AccessCodeLength.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Unknown:
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                } // switch
                            } // for
                        } // if
                        else
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("[Data Update Notification] Container isn't an AccessCode type\r\n"));
                        } // if
                    }
                    break;

                case DataContainer.AccessCodeAttributes:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("AccessCodeAttributes Notification:\r\n"));
                        IAccessCodeAttributes container = (clsDataContainer as IAccessCodeAttributes);
                        if (container != null)
                        {
                            IRepository repository = ptrSender.Repository;
                            IAccessCode accesscode = repository.GetAccessCodeBySystemIndex(container.SystemIndex);
                            UInt32 num_accesscode = accesscode.SystemIndex;
                            accesscode.Dispose();
                            repository.Dispose();
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.Attributes:
                                        {
                                        }
                                        break;
                                    case SecurityDataSelector.AccessCode_BellSquawk:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Bell Squawk = " + Enum.GetName(typeof(AccessCodeAttributesBellSquawkState), container.BellSquawk).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AccessCode_CanBypassZone:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Can Bypass Zone = " + Enum.GetName(typeof(AccessCodeAttributesCanBypassZoneState), container.CanBypassZone).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AccessCode_DuressCode:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Duress Code = " + Enum.GetName(typeof(AccessCodeAttributesDuressCodeState), container.DuressCode).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AccessCode_OneTimeUse:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " One Time Use = " + Enum.GetName(typeof(AccessCodeAttributesOneTimeUseState), container.OneTimeUse).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AccessCode_RemoteAccessEnabled:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Remote Access Enabled = " + Enum.GetName(typeof(AccessCodeAttributesRemoteAccessState), container.RemoteAccessEnabled).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AccessCode_Supervisor:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("AccessCode " + num_accesscode.ToString() + " Supervisor = " + Enum.GetName(typeof(AccessCodeAttributesSupervisorState), container.Supervisor).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Unknown:
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                }
                            }
                        }
                        else
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("[Data Update Notification] Container isn't an AccessCodeAttributes type\r\n"));
                        } // if
                    }
                    break;

                case DataContainer.Partition:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("Partition Notification:\r\n"));
                        IPartition container = (clsDataContainer as IPartition);
                        if (container != null)
                        {
                            UInt32 num_partition = container.SystemIndex;
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.SystemIndex:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition System Index = " + container.SystemIndex.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Label:
                                        {
                                            // the panel appends a "\0" null char at the end of the string. And there may be some garbage bytes after the NULL.
                                            string aLabel = container.Label.ToString();
                                            if (false != aLabel.Contains("\0"))
                                            {
                                                aLabel = aLabel.Substring(0, aLabel.IndexOf("\0"));
                                            }
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Label = " + aLabel + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionArmingLevelStatus:
                                        {
                                            if (PartitionArmedState.UserArmed != container.PartitionStateData.PartitionArmed)
                                            {
                                                OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Arming Level Status = " + Enum.GetName(typeof(PartitionArmedState), container.PartitionStateData.PartitionArmed).ToString() + "\r\n"));
                                            }
                                            else
                                            {
                                                ITextString auxContainer = (clsAuxDataContainer as ITextString);
                                                OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() +
                                                    " Arming Level Status = " + Enum.GetName(typeof(PartitionArmedState),
                                                    container.PartitionStateData.PartitionArmed).ToString() +
                                                    " By User " + auxContainer.Text.ToString() + "\r\n"));
                                            }
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionEntryDelayStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Entry Delay Status = " + Enum.GetName(typeof(PartitionEntryDelayState), container.PartitionStateData.PartitionEntryDelay).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionExitDelayStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Exit Delay Status = " + Enum.GetName(typeof(PartitionExitDelayState), container.PartitionStateData.PartitionExitDelay).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionBusyStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Busy Status = " + Enum.GetName(typeof(PartitionBusyState), container.PartitionStateData.PartitionBusy).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionBypassStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Bypass Status = " + Enum.GetName(typeof(PartitionBypassState), container.PartitionStateData.PartitionBypass).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionBlankStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Blank Status = " + Enum.GetName(typeof(PartitionBlankState), container.PartitionStateData.PartitionBlank).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionTroubleStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Trouble Status = " + Enum.GetName(typeof(PartitionTroubleState), container.PartitionStateData.PartitionTrouble).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionAlarmInMemoryStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Alarm In Memory Status = " + Enum.GetName(typeof(PartitionAlarmMemoryState), container.PartitionStateData.PartitionAlarmMemory).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionAudibleBellStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Audible Bell Status = " + Enum.GetName(typeof(PartitionAudibleBellState), container.PartitionStateData.PartitionAudibleBellState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionAudibleBellType:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Audible Bell Type = " + Enum.GetName(typeof(PartitionAudibleBellType), container.PartitionStateData.PartitionAudibleBellType).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionQuickExitStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Quick Exit Status = " + Enum.GetName(typeof(PartitionQuickExitState), container.PartitionStateData.PartitionQuickExit).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionReadyStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Ready Status = " + Enum.GetName(typeof(PartitionReadyState), container.PartitionStateData.PartitionReady).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionBuzzerStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Buzzer Status = " + Enum.GetName(typeof(PartitionBuzzerState), container.PartitionStateData.PartitionBuzzer).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionAlarmStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Alarm Status = " + Enum.GetName(typeof(PartitionAlarmState), container.PartitionStateData.PartitionAlarm).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.PartitionDoorChimeStatus:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Door Chime Status = " + Enum.GetName(typeof(DoorChimeEnabledState), container.DoorChimeEnabled).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AlarmTypes:
                                        {
                                            string strAlarms = string.Empty;
                                            AlarmType[] alarms = container.AlarmTypes;
                                            for (int j = 0; j < alarms.Length; j++)
                                            {
                                                strAlarms += Enum.GetName(typeof(AlarmType), alarms[j]).ToString() + "\r\n";
                                            } // for
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + num_partition.ToString() + " Alarms: \r\n" + strAlarms));
                                        }
                                        break;
                                    case SecurityDataSelector.Unknown:
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                } // switch
                            } // for
                        }
                        else
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("[Data Update Notification] Container isn't a Partition type\r\n"));
                        } // if
                    }
                    break;

                case DataContainer.Zone:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("Zone Notification:\r\n"));
                        IZone container = (clsDataContainer as IZone);
                        if (container != null)
                        {
                            UInt32 num_zone = container.SystemIndex;
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.SystemIndex:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone System Index = " + container.SystemIndex.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Label:
                                        {
                                            // the panel is appends a "\0" null char at the end of the string. And there may be some garbage bytes after the NULL.
                                            string aLabel = container.Label.ToString();
                                            if (false != aLabel.Contains("\0"))
                                            {
                                                aLabel = aLabel.Substring(0, aLabel.IndexOf("\0"));
                                            }
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Label = " + aLabel + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.OpenClose:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Open/Close = " + Enum.GetName(typeof(ZoneOpenCloseState), container.OpenCloseState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Bypass:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Bypass = " + Enum.GetName(typeof(ZoneBypassState), container.BypassState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AlarmInMemory:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Alarm In Memory = " + Enum.GetName(typeof(ZoneAlarmInMemoryState), container.AlarmInMemoryState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Alarm:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Alarm = " + Enum.GetName(typeof(ZoneAlarmState), container.AlarmState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Delinquency:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Delinquency = " + Enum.GetName(typeof(ZoneDelinquencyState), container.DelinquencyState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.LowBattery:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Low Battery = " + Enum.GetName(typeof(ZoneLowBatteryState), container.LowBatteryState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Fault:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Fault = " + Enum.GetName(typeof(ZoneFaultState), container.FaultState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Tamper:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Tamper = " + Enum.GetName(typeof(ZoneTamperState), container.TamperState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.LowSensitivity:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Low Sensitivity = " + Enum.GetName(typeof(ZoneLowSensitivityState), container.LowSensitivityState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Masked:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Masked = " + Enum.GetName(typeof(ZoneMaskedState), container.MaskedState).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AlarmTypes:
                                        {
                                            string pstring = DataContainer.Unknown.ToString();
                                            IPartition auxContainer = (clsAuxDataContainer as IPartition);
                                            if (auxContainer != null)
                                            {
                                                pstring = auxContainer.SystemIndex.ToString();
                                            }
                                            string strAlarms = string.Empty;
                                            AlarmType[] alarms = container.AlarmTypes;
                                            for (int j = 0; j < alarms.Length; j++)
                                            {
                                                strAlarms += Enum.GetName(typeof(AlarmType), alarms[j]).ToString() + "\r\n";
                                            } // for
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Partition " + pstring + " Zone " + num_zone.ToString() + " Alarms: \r\n" + strAlarms));
                                        }
                                        break;
                                    case SecurityDataSelector.Unknown:
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                } // switch
                            } // for
                        }
                        else
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("[Data Update Notification] Container isn't a Zone type\r\n"));
                        } // if
                    }
                    break;

                case DataContainer.ZoneAttributes:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("ZoneAttributes Notification:\r\n"));
                        IZoneAttributes container = (clsDataContainer as IZoneAttributes);
                        if (container != null)
                        {
                            IRepository repository = ptrSender.Repository;
                            IZone zone = repository.GetZoneBySystemIndex(container.SystemIndex);
                            UInt32 num_zone = zone.SystemIndex;
                            zone.Dispose();
                            repository.Dispose();
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.Attributes:
                                        {
                                        }
                                        break;
                                    case SecurityDataSelector.Zone_BypassEnable:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Bypass Enable = " + Enum.GetName(typeof(ZoneAttributesBypassEnableState), container.BypassEnable).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Zone_ChimeFunction:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Zone " + num_zone.ToString() + " Chime Function = " + Enum.GetName(typeof(ZoneAttributesChimeFunctionState), container.ChimeFunction).ToString() + "\r\n"));
                                        }
                                        break;
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                }
                            }
                        }
                        else
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("[Data Update Notification] Container isn't a Zone Attributes type\r\n"));
                        } // if
                    }
                    break;

                case DataContainer.VirtualZone:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("VirtualZone Notification:\r\n"));

                        IVirtualZone container = (clsDataContainer as IVirtualZone);
                        if (container != null)
                        {
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.ZoneNumber:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("VirtualZone ZoneNumber = " + container.ZoneNumber.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.SystemIndex:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("VirtualZone System Index = " + container.SystemIndex.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.Unknown:
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                } // switch
                            } // for
                        }
                        else
                        {
                            OnDebugEvent(ptrSender, new DebugEventArgs("[Data Update Notification] Container isn't a VirtualZone type\r\n"));
                        } // if
                    }
                    break;

                case DataContainer.VirtualZoneStatus:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("VirtualZoneStatus Notification:\r\n"));
                        IVirtualZoneStatus container = (clsDataContainer as IVirtualZoneStatus);
                        if (container != null)
                        {
                            IRepository repository = ptrSender.Repository;
                            IVirtualZone vzone = repository.GetVirtualZoneBySystemIndex(container.SystemIndex);
                            UInt32 num_vzone = vzone.SystemIndex;
                            vzone.Dispose();
                            repository.Dispose();
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.VirtualZoneStatus:
                                        {
                                        }
                                        break;
                                    case SecurityDataSelector.VirtualZone_ACTrouble:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Virtual Zone " + num_vzone.ToString() + " ACTrouble Status = " + Enum.GetName(typeof(VirtualZoneStatusACTroubleState), container.ACTrouble).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.VirtualZone_Fault:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Virtual Zone " + num_vzone.ToString() + " Fault Status = " + Enum.GetName(typeof(VirtualZoneStatusFaultState), container.Fault).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.VirtualZone_LowBattery:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Virtual Zone " + num_vzone.ToString() + " LowBattery Status = " + Enum.GetName(typeof(VirtualZoneStatusLowBatteryState), container.LowBattery).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.VirtualZone_Open:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Virtual Zone " + num_vzone.ToString() + " Open Status = " + Enum.GetName(typeof(VirtualZoneStatusOpenState), container.Open).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.VirtualZone_Tamper:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Virtual Zone " + num_vzone.ToString() + " Tamper Status = " + Enum.GetName(typeof(VirtualZoneStatusTamperState), container.Tamper).ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.VirtualZone_Masked:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Virtual Zone " + num_vzone.ToString() + " Masked Status = " + Enum.GetName(typeof(VirtualZoneStatusMaskedState), container.Masked).ToString() + "\r\n"));
                                        }
                                        break;
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                }
                            }
                        }
                    }
                    break;

                case DataContainer.SystemManager:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("SystemManager Notification:\r\n"));
                        ISystemManager container = (clsDataContainer as ISystemManager);
                        if (container != null)
                        {
                            for (int i = 0; i < tblDataSelectors.Length; ++i)
                            {
                                switch (tblDataSelectors[i])
                                {
                                    case SecurityDataSelector.SystemManager_TroublePresent:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Trouble Present = " + container.TroublePresent.ToString() + "\r\n"));
                                        }
                                        break;
                                    case SecurityDataSelector.AlarmTypes:
                                        {
                                            string strAlarms = string.Empty;
                                            AlarmType[] alarms = container.AlarmTypes;
                                            for (int j = 0; j < alarms.Length; j++)
                                            {
                                                strAlarms += Enum.GetName(typeof(AlarmType), alarms[j]).ToString() + "\r\n";
                                            } // for
                                            OnDebugEvent(ptrSender, new DebugEventArgs("SystemManager Alarms: \r\n" + strAlarms));
                                        }
                                        break;
                                    case SecurityDataSelector.Unknown:
                                    default:
                                        {
                                            OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Security Data Selector - " + Enum.GetName(typeof(SecurityDataSelector), tblDataSelectors[i]) + "\r\n"));
                                        }
                                        break;
                                }
                            }
                        }
                    }
                    break;

                case DataContainer.Unknown:
                default:
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("Unknown Data Container - " + Enum.GetName(typeof(DataContainer), clsDataContainer.ContainerType) + "\r\n"));
                    }
                    break;
            } // switch

            // do cleanup
            if (clsDataContainer != null)
            {
                clsDataContainer.Dispose();
            }
            if (clsAuxDataContainer != null)
            {
                clsAuxDataContainer.Dispose();
            }
        }
        #endregion

        #region Channel Events
        private void channel_StateNotificationEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification, uint flgFlags)
        {
            //OnDebugEvent(ptrSender, new DebugEventArgs("[Channel State Notification Event]\r\n"));
        }

        private void channel_SendDataPacketEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification, byte[] bufData)
        {
            //OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Send Data Packet Event]\r\n"));

            if (ptrSender == null)
            {
                return;
            } // if

            try
            {
                SessionKey key = (ptrSender.Tag as SessionKey);
                if (key == null)
                {
                    OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Cannot send the data packet because the session key is missing!\r\n"));
                    return;
                } // if

                switch (key.sessiontype)
                {
                    case SessionTypes.UDP:
                        lock (_udpsessionslock)
                        {
                            if (_udpsessions.ContainsKey(key) == true)
                            {
                                UDPPoint udp = _udpsessions[key].UDPPoint;
                                if (udp != null)
                                {
                                    if (udp.SendTo(_udpsessions[key].PeerAddress, bufData, bufData.Length, Constants.SEND_TIMEOUT) != bufData.Length)
                                    {
                                        OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Failed to send all UDP data!\r\n"));
                                    } // if
                                }
                                else
                                {
                                    OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Missing UDP connection point!\r\n"));
                                } // if
                            }
                            else
                            {
                                OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Failed to find UDP session!\r\n"));
                            } // if
                        } // lock
                        break;
                    case SessionTypes.TCP:
                        lock (_tcpsessionslock)
                        {
                            if (_tcpsessions.ContainsKey(key) == true)
                            {
                                TCPProxy tcp = _tcpsessions[key].TCPProxy;
                                if (tcp != null)
                                {
                                    if (tcp.Send(bufData, bufData.Length, Constants.SEND_TIMEOUT) != bufData.Length)
                                    {
                                        OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Failed to send all TCP data!\r\n"));
                                    } // if
                                }
                                else
                                {
                                    OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Missing TCP connection proxy!\r\n"));
                                } // if
                            }
                            else
                            {
                                OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Failed to find TCP session!\r\n"));
                            } // if
                        } // lock
                        break;
                    default:
                        OnDebugEvent(ptrSender, new DebugEventArgs("[channel_SendDataPacketEvent]: Unknown session type!\r\n"));
                        break;
                } // switch
            }
            catch (Exception e)
            {
                OnExceptionEvent(ptrSender, new ExceptionEventArgs(e));
            } // try
        }

        private void channel_PacketReceivedEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification, byte[] bufData)
        {
            //OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Packet Received Event]\r\n"));
        }

        private void channel_InspectPayloadEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification, byte[] bufData)
        {
            // display data received
            //OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Inspect Payload Event]\r\n"));

            if (ptrSender == null)
            {
                return;
            } // if

            try
            {
                if (bufData != null)
                {
                    string channel = "UNKNOWN";
                    SessionKey key = (ptrSender.Tag as SessionKey);
                    if (key != null)
                    {
                        if (key.sessiontype == SessionTypes.TCP)
                        {
                            channel = "TCP";
                        }
                        else if (key.sessiontype == SessionTypes.UDP)
                        {
                            channel = "UDP";
                        } // if
                    }
                    else
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Inspect Payload Event]: Session key is mising!\r\n"));
                    } // if
                    if (bufData.Length > 0)
                    {
                        ushort cmd;
                        string cmd_msg;
                        if (bufData[0] == 0x04)
                        {
                            cmd = GetUInt16(bufData, 1);
                            cmd_msg = "Low_Level_ACK";
                        }
                        else
                        {
                            // command (check data size - MSB set means 2 length bytes)
                            if ((bufData[0] & 0x80) == 0x80)
                            {
                                cmd = GetUInt16(bufData, 4);
                            }
                            else
                            {
                                cmd = GetUInt16(bufData, 3);
                            } // if
                            cmd_msg = "Command";
                        } // if
                        string bytes = BitConverter.ToString(bufData).Replace('-', ' ');
                        OnDebugEvent(ptrSender, new DebugEventArgs("{" + channel.ToString() + "} RAW " + ((flgNotification == ChannelEvent.IncomingData) ? "RX " : "TX ") + cmd.ToString("X04") + " [" + cmd_msg.ToString() + "]\r\n"));
                        OnDebugEvent(ptrSender, new DebugEventArgs(bytes + "\r\n"));
                    }
                    else
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("{" + channel.ToString() + "} RAW " + ((flgNotification == ChannelEvent.IncomingData) ? "RX " : "TX ") + "[no data received]\r\n"));
                    } // if
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(ptrSender, new ExceptionEventArgs(e));
            } // try
        }

        private void channel_EventNotificationEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification)
        {
            OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Event Notification Event] - " + Enum.GetName(typeof(ChannelEvent), flgNotification) + "\r\n"));

            if (ptrSender == null)
            {
                return;
            } // if

            try
            {
                // strText is the intergrationid
                string bkey = strText.ToString();

                // check channel event
                if ((flgNotification == ChannelEvent.ChannelClosing) ||
                    (flgNotification == ChannelEvent.ChannelDeleted))
                {
                    DisconnectChannelEvents(ptrSender);

                    SessionKey key = (ptrSender.Tag as SessionKey);
                    if (key == null)
                    {
                        OnDebugEvent(ptrSender, new DebugEventArgs("[channel_EventNotificationEvent]: Cannot delete the session because the session key is missing!\r\n"));
                        return;
                    } // if

                    switch (key.sessiontype)
                    {
                        case SessionTypes.UDP:
                            lock (_udpsessionslock)
                            {
                                if (_udpsessions.ContainsKey(key) == true)
                                {
                                    UDPPoint udp = _udpsessions[key].UDPPoint;
                                    if (udp != null)
                                    {
                                        //_udpsessions[key].UDPPoint.Shutdown();
                                        _udpsessions[key].UDPPoint = null;
                                    } // if
                                    _udpsessions.Remove(key);
                                } // if
                            } // lock
                            break;
                        case SessionTypes.TCP:
                            lock (_tcpsessionslock)
                            {
                                if (_tcpsessions.ContainsKey(key) == true)
                                {
                                    TCPProxy tcp = _tcpsessions[key].TCPProxy;
                                    if (tcp != null)
                                    {
                                        _tcpserver.ShutProxy(tcp);
                                    } // if
                                    _tcpsessions.Remove(key);
                                } // if
                            } // lock
                            break;
                        default:
                            OnDebugEvent(ptrSender, new DebugEventArgs("[channel_EventNotificationEvent]: Unknown session type!\r\n"));
                            break;
                    } // switch
                    ptrSender.Tag = null;
                }
                else if (flgNotification == ChannelEvent.PeerIdentified)
                {
                    lock (_securitybaseslock)
                    {
                        if (_securitybases.ContainsKey(bkey) == true)
                        {
                            // we already have a security base for this account
                            _securitybases[bkey].AddChannel(ptrSender);
                            return;
                        }
                        else
                        {
                            // don't have a security base for this account, check the data base to see if this
                            // account is allowed to talk to us
                            ParamParser parser = new ParamParser();
                            parser.AddValue(Parameters.Query_Category, Parameters.Query_Category_ITV2);
                            parser.AddValue(Parameters.Query_Selector, Parameters.Query_Selector_Account_Info);
                            parser.AddValue(Parameters.ITV2_Param_Identifier, bkey);
                            parser.AddValue(Parameters.ITV2_Param_Connection, ptrSender.ConnectionInfo);
                            string query = _datastore.SelectData(parser.ToString());
                            if (query != string.Empty)
                            {
                                // query was successful, create securitybase
                                _securitybases.Add(bkey, _sdk.CreateSecurityBase(TSP.DSC_InteractiveSDK.ProtocolType.ITV2));
                                // add channel to security base
                                _securitybases[bkey].AddChannel(ptrSender);
                                parser.Clear();
                                parser.Parse(query);
                                string code = parser.GetValue(ExtendedParameters.ITV2_Param_InstallersCode);
                                if (code != string.Empty)
                                {
                                    // database entry has installers code
                                    IAccessCredentials credentials = _sdk.CreateAccessCredentials(AccessCredentialsType.Numeric);
                                    credentials.CredentialsString = code;
                                    _securitybases[bkey].InstallerCredentials = credentials;
                                } // if
                                ConnectSecurityEvents(_securitybases[bkey]);
                                return;
                            } // if
                        } // if
                    } // lock
                    OnDebugEvent(ptrSender, new DebugEventArgs("[channel_EventNotificationEvent] Security base " + strText.ToString() + " not found!\r\n"));
                }
                else if (flgNotification == ChannelEvent.ChannelRxIdle)
                {
                    OnDebugEvent(ptrSender, new DebugEventArgs("[channel_EventNotificationEvent] The " + strText.ToString() + " channel's rx is idle!\r\n"));
                }
                else if (flgNotification == ChannelEvent.ChannelTxIdle)
                {
                    OnDebugEvent(ptrSender, new DebugEventArgs("[channel_EventNotificationEvent] The " + strText.ToString() + " channel's tx is idle!\r\n"));
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(ptrSender, new ExceptionEventArgs(e));
            } // try
        }

        private void channel_ErrorNotificationEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification, ChannelError flgError)
        {
            OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Error Notification Event] Event: " + Enum.GetName(typeof(ChannelEvent), flgNotification) + " Error: " + Enum.GetName(typeof(ChannelError), flgError) + "\r\n"));
        }

        private void channel_DataProcessingEvent(IChannel ptrSender, string strText, ChannelEvent flgNotification, IProtocolData clsProtocolData)
        {
            //OnDebugEvent(ptrSender, new DebugEventArgs("[Channel Data Processing Event]\r\n"));
        }
        #endregion
    }
    #endregion

}
