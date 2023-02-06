using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Net;
using System.Net.Sockets;
using System.Diagnostics;
using System.Threading;

namespace NET_TestApp
{
    public class AddressInfo
    {
        public AddressFamily Family  = AddressFamily.Unspecified;
        public string        Address = string.Empty;
        public int           Port    = 0;

        public AddressInfo()
        {
        }

        public AddressInfo(AddressInfo other)
        {
            Clear();
            Family  = other.Family;
            Address = other.Address;
            Port    = other.Port;
        }

        public void Clear()
        {
            Family  = AddressFamily.Unspecified;
            Address = string.Empty;
            Port    = 0;
        }

        public static bool operator >(AddressInfo left, AddressInfo right)
        {
            if (left.Family > right.Family)
            {
                return (true);
            } // if

            if (string.Compare(left.Address, right.Address) > 0)
            {
                return (true);
            } // if

            if (left.Port > right.Port)
            {
                return (true);
            } // if

            return (false);
        }

        public static bool operator <(AddressInfo left, AddressInfo right)
        {
            if (left.Family < right.Family)
            {
                return (true);
            } // if

            if (string.Compare(left.Address, right.Address) < 0)
            {
                return (true);
            } // if

            if (left.Port < right.Port)
            {
                return (true);
            } // if

            return (false);
        }

        public static bool operator ==(AddressInfo left, AddressInfo right)
        {
            return (left.Equals(right));
        }

        public static bool operator !=(AddressInfo left, AddressInfo right)
        {
            return (!(left.Equals(right)));
        }

        public override bool Equals(object obj)
        {
            AddressInfo other = (obj as AddressInfo);

            if (object.ReferenceEquals(other, null) == true)
            {
                return (false);
            } // if

            if ((this.Family == other.Family) && (this.Port == other.Port) &&
                (0 == string.Compare(this.Address, other.Address)))
            {
                return (true);
            } // if

            return (false);
        }

        public override int GetHashCode()
        {
            string hash_string = string.Empty;

            hash_string += this.Address;
            hash_string += this.Port.ToString();
            hash_string += this.Family.ToString();

            return (hash_string.GetHashCode());
        }
    }

    public class SocketEventArgs : EventArgs
    {
        private AddressInfo _localaddress;
        private AddressInfo _remoteaddress;
        private byte[]      _databuffer;

        public SocketEventArgs()
        {
            _localaddress = new AddressInfo();
            _remoteaddress = new AddressInfo();
        }

        public AddressInfo localaddress
        {
            get { return (_localaddress); }
            set { _localaddress = value; }
        }

        public AddressInfo remoteaddress
        {
            get { return (_remoteaddress); }
            set { _remoteaddress = value; }
        }

        public byte[] databuffer
        {
            get { return (_databuffer); }
            set { _databuffer = value; }
        }
    }

    public class ExceptionEventArgs : EventArgs
    {
        private Exception _exception;

        public ExceptionEventArgs(Exception exception)
        {
            _exception = exception;
        }

        public Exception Exception
        {
            get { return (_exception); }
            set { _exception = value; }
        }
    }

    public enum ThreadStatus
    {
        Unknown = 0,	//the thread is unknown
        Stopped,		//the thread has stopped
        Started,		//the thread has started
        Stopping,		//the thread is stopping
        Starting,		//the thread is starting
        Shutdown		//the thread shutdown requested
    }

    public enum SocketStatus
    {
    	IS_SUCCESS,
    	IS_FAILURE,
    	IS_TIMEOUT
    }

    public enum SocketQuery
    {
        QUERY_SEND,
        QUERY_READ,
        QUERY_CONNECT,
        QUERY_ACCEPT,
        QUERY_ERRORS
    }

    #region Socket
    public class ipsocket
    {
        #region Constants
        private const int SOCKET_uSEC_PER_MSEC = 1000;
        private const int SOCKET_MAX_BACKLOG   = 5;	//maximum number of queued requests; default: 5
        private const int SOCKET_SEND_TIMEOUT  = 2000;	//timout [ms] when sending data
        private const int SOCKET_RECV_TIMEOUT  = 2000;	//timout [ms] when receiving data
        #endregion

        #region Variables
        private Socket        _socket     = null;
        private AddressFamily _family     = AddressFamily.Unspecified;
        private ProtocolType  _protocol   = ProtocolType.Unspecified;
        #endregion

        #region Constructor
        public ipsocket()
        {
        }

        ~ipsocket()
        {
        }
        #endregion

        #region Properties
        public Socket socket
        {
            get { return (_socket); }
            set { _socket = value; }
        }

        public AddressFamily family
        {
            get { return (_family); }
            set { _family = value; }
        }

        public ProtocolType protocol
        {
            get { return (_protocol); }
            set { _protocol = value; }
        }
        #endregion

        #region Public Methods
        public bool Create(AddressFamily family, ProtocolType proto, bool blocking)
        {
            try
            {
                if (_socket == null)
                {
                    if (((AddressFamily.InterNetwork == family) || (AddressFamily.InterNetworkV6 == family)) &&
                        ((ProtocolType.Tcp == proto) || (ProtocolType.Udp == proto)))
                    {
                        SocketType type = ((ProtocolType.Tcp == proto) ? SocketType.Stream : SocketType.Dgram);

                        _socket = new Socket(family, type, proto);

                        _family   = family;
                        _protocol = proto;

                        _socket.SendTimeout    = SOCKET_SEND_TIMEOUT;
                        _socket.ReceiveTimeout = SOCKET_RECV_TIMEOUT;

                        return (SetBlocking(blocking));
                    } // if
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));   
            } // try

            return (false);
        }

        public bool Shutdown(SocketShutdown how)
        {
            try
            {
                if (_socket != null)
                {
                    try { _socket.Shutdown(how); } catch {}
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool Close()
        {
            try
            {
                if (_socket != null)
                {
                    try { _socket.Close(); } catch {}
                    _socket = null;
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));   
            } // try
            return (false);
        }

        public bool SetBlocking(bool enabled)
        {
            try
            {
                if (_socket != null)
                {
                    _socket.Blocking = enabled;
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool SetExclusiveAddressUse(bool enabled)
        {
            try
            {
                if (_socket != null)
                {
                    _socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.ExclusiveAddressUse, enabled);
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));   
            } // try

            return (false);
        }

        public bool SetNoDelay(bool enabled)
        {
            try
            {
                if (_socket != null)
                {
                    _socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.NoDelay, enabled);
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));   
            } // try

            return (false);
        }

        public bool SetLingerState(bool enabled, bool linger, int timeout)
        {
            try
            {
                if (_socket != null)
                {
                    _socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.DontLinger, enabled);
                    if (enabled == true)
                    {
                        _socket.SetSocketOption(SocketOptionLevel.Socket, SocketOptionName.Linger, new LingerOption(linger, timeout));
                        return (true);
                    } // if
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool Connect(string address, int port)
        {
            try
            {
                if (_socket != null)
                {
                    IPAddress addr;
                    if (IPAddress.TryParse(address, out addr) == true)
                    {
                        _socket.Connect(addr, port);
                        return (true);
                    } // if
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool Bind(string address, int port)
        {
            try
            {
                if (_socket != null)
                {
                    IPAddress addr;
                    if (IPAddress.TryParse(address, out addr) == true)
                    {
                        IPEndPoint ep = new IPEndPoint(addr, port);
                        _socket.Bind((EndPoint)ep);
                        return (true);
                    } // if
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool GetLocalHost(ref AddressFamily family, ref string address, ref int port)
        {
            family  = AddressFamily.Unspecified;
            address = string.Empty;
            port    = 0;
            try
            {
                if (_socket != null)
                {
                    family = _socket.LocalEndPoint.AddressFamily;
                    IPEndPoint ep = (IPEndPoint)_socket.LocalEndPoint;
                    address = ep.Address.ToString();
                    port = ep.Port;
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool GetRemoteHost(ref AddressFamily family, ref string address, ref int port)
        {
            family = AddressFamily.Unspecified;
            address = string.Empty;
            port = 0;
            try
            {
                if (_socket != null)
                {
                    family = _socket.RemoteEndPoint.AddressFamily;
                    IPEndPoint ep = (IPEndPoint)_socket.RemoteEndPoint;
                    address = ep.Address.ToString();
                    port = ep.Port;
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public SocketStatus Query(SocketQuery flgQuery, int numTimeout) //the timeout is in [ms]
        {
	        if (null != _socket)
	        {
		        //validate the timeout
		        if (numTimeout < 0) numTimeout = 0;
		
		        bool flgResult = false;
		        switch (flgQuery)
		        {
			        case SocketQuery.QUERY_READ:
			        case SocketQuery.QUERY_ACCEPT:
                        flgResult = _socket.Poll((numTimeout * SOCKET_uSEC_PER_MSEC), SelectMode.SelectRead);
				        if (true == flgResult) 
				        {
					        return SocketStatus.IS_SUCCESS;	//ready to receive data
				        } 
                        else
				        {
					        return SocketStatus.IS_TIMEOUT;	//timeout
				        }
			        case SocketQuery.QUERY_SEND: 
			        case SocketQuery.QUERY_CONNECT:
                        flgResult = _socket.Poll((numTimeout * SOCKET_uSEC_PER_MSEC), SelectMode.SelectWrite);
				        if (true == flgResult) 
				        {
					        return SocketStatus.IS_SUCCESS;	//ready to transmit data
				        } 
                        else
				        {
					        return SocketStatus.IS_TIMEOUT;	//timeout
				        }
			        case SocketQuery.QUERY_ERRORS: 
                        flgResult = _socket.Poll((numTimeout * SOCKET_uSEC_PER_MSEC), SelectMode.SelectError);
				        if (true == flgResult) 
				        {
					        return SocketStatus.IS_SUCCESS;	//errors present
				        } 
                        else
				        {
					        return SocketStatus.IS_TIMEOUT;	//timeout
				        }
		        }
	        }
	        //failure
	        return SocketStatus.IS_FAILURE;
        }

        public int Send(byte[] data, int size, int offset = 0)
        {
            if (null != _socket)
            {
                return (_socket.Send(data, offset, size, SocketFlags.None));
            }

            return (-1);
        }

        public int SendTo(string address, int port, byte[] data, int size, int offset = 0)
        {
            if (_socket != null)
            {
                IPAddress addr;
                if (IPAddress.TryParse(address, out addr) == true)
                {
                    IPEndPoint ep = new IPEndPoint(addr, port);
                    return (_socket.SendTo(data, offset, size, SocketFlags.None, (EndPoint)ep));
                } // if
            } // if

            return (-1);
        }

        public int Read(byte[] data, int size, int offset = 0)
        {
            if (_socket != null)
            {
                return (_socket.Receive(data, offset, size, SocketFlags.None));
            } // if

            return (-1);
        }

        public int ReadFrom(ref AddressFamily family, ref string address, ref int port, byte[] data, int size, int offset = 0)
        {
            if (_socket != null)
            {
                if (null != address)
                {
                    IPEndPoint ipep = new IPEndPoint(IPAddress.Any, 0);
                    EndPoint ep = (EndPoint)ipep;
                    int read = _socket.ReceiveFrom(data, offset, size, SocketFlags.None, ref ep);
                    if (0 <= read)
                    {
                        family = ep.AddressFamily;
                        address = ((IPEndPoint)ep).Address.ToString();
                        port = ((IPEndPoint)ep).Port;
                        return read;
                    }
                }
                else
                {
                    return _socket.Receive(data, size, SocketFlags.None);
                } // if
            } // if

            return (-1);
        }

        public bool Listen(int backlog = SOCKET_MAX_BACKLOG)
        {
            try
            {
                if (_socket != null)
                {
                    _socket.Listen(backlog);
                    return (true);
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        public bool Accept(ipsocket socket, ref AddressFamily family, ref string address, ref int port)
        {
            try
            {
                if (_socket != null)
                {
                    Socket new_socket = _socket.Accept();

                    family = new_socket.RemoteEndPoint.AddressFamily;
                    IPEndPoint ep = (IPEndPoint)new_socket.RemoteEndPoint;
                    address = ep.Address.ToString();
                    port = ep.Port;

                    if (socket != null)
                    {
                        if (socket._socket == null)
                        {
                            socket._socket = new_socket;
                            socket._family = family;
                            socket._protocol = this._protocol;
                            return (true);
                        } // if
                    } // if
                    try { new_socket.Close(); } catch { }
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }
        #endregion

        #region Events
        public event EventHandler<ExceptionEventArgs> ExceptionEvent;

        private void OnExceptionEvent(object sender, ExceptionEventArgs e)
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
        #endregion
    }
    #endregion

    #region THREADED TCP & UDP
    public abstract class threadclass
    {
        #region Constants
        private   const int THREAD_IDLE_SLEEP = 0;		//processing sleep time [ms] (0 - just switch threads)
        protected const int THREAD_STOP_SLEEP = 1;		//stopping sleep time in [ms]
        protected const int THREAD_STOP_COUNT = 1000;	//stoping delay in units of THREAD_STOP_SLEEP[ms]
        #endregion

        #region Variables
        private object                m_objThreadLock = null;	            //critical section
        private volatile Thread       m_clsThread = null;                   //thread type
        private volatile ThreadStatus m_flgStatus = ThreadStatus.Unknown;   //thread state
        #endregion

        #region Constructor
        public threadclass()
        {
            m_objThreadLock = new object();
        }

        ~threadclass()
        {
            //try stopping the thread
            if (false == Stop(THREAD_STOP_COUNT))
            {
                //the thread failed to stop
            }
        }
        #endregion

        #region Public Methods
        public ThreadStatus GetStatus()
        {
            lock (m_objThreadLock)
            {
                return (m_flgStatus);
            }
        }

        public bool TestThread()
        {
            lock(m_objThreadLock)
            {
		        if ((ThreadStatus.Unknown != m_flgStatus) &&
        			(ThreadStatus.Stopped != m_flgStatus))
		        {
        			//compare active threads
                	//get current thread id
                    int current = Thread.CurrentThread.ManagedThreadId;
                    int another = m_clsThread.ManagedThreadId;

                	//compare thread IDs
	                return ((current == another)? true : false);
		        }
		        //different threads
		        return false;
            }
        }

        public virtual bool Start(int numPriority = 0)
        {
            lock (m_objThreadLock)
            {
			    //check if the thread is present
			    if ((ThreadStatus.Unknown != m_flgStatus) &&
				    (ThreadStatus.Stopped != m_flgStatus))
			    {
				    //cannot re-initialize the thread right now
				    return false;
			    }

			    //create new thread
			    Thread thread = null;
                if (null != (thread = new Thread(() => ThreadMain(this))))
			    {
                    thread.Name = "threadclass";
				    //set thread priority
                    thread.Priority = ThreadPriority.Normal;

				    //the thread is starting
				    m_clsThread = thread;
				    m_flgStatus = ThreadStatus.Starting;
                    thread.Start();
			    }
			    else
			    {
				    //cannot start the new thread
				    m_clsThread = null;
				    m_flgStatus = ThreadStatus.Unknown;
				    return false;
			    }
            }

    		//wait for the thread to start (or stop - in case of a problem)
		    while (ThreadStatus.Starting == GetStatus())
		    {
    			//take a nap
                Thread.Sleep(THREAD_IDLE_SLEEP);
		    }
	
    		//check whether the thread has started
            return ((ThreadStatus.Started == GetStatus()) ? true : false);
        }

	    //The timeout 0 is used to stop the thread without veryfying 
	    //whether the thread has actualy stopped.
	    //(if the timeout has not been specified, do not try to verify thread
	    //state or access any other members of this class because the class
	    //might have been deleted - that's what the timeout 0 is used for)
	    public virtual bool Stop(int numTimeout = 0)
	    {
		    //check if the created thread tries to stop itself
		    //(this function must be called from a thread different
		    //than the encapsulated thread or otherwise a deadlock
		    //may happen)
		    if (false != TestThread())
		    {
			    //create temporary, 'shutdown' thread 
			    //and quit immediately to avoid deadlock
			    Thread thread = null;
                return (((thread = new Thread(() => ThreadShut(this))) == null) ? false : true);
		    }

		    //enter critical section
            lock(m_objThreadLock)
            {
			    //check if the thread is already stopped
			    if ((ThreadStatus.Unknown == m_flgStatus) ||
				    (ThreadStatus.Stopped == m_flgStatus))
			    {
				    //thread is already stopped
				    return true;
			    }

			    //check if the thread is currently running
			    if ((ThreadStatus.Starting == m_flgStatus) ||
				    (ThreadStatus.Started == m_flgStatus))
			    {
				    //signal the thread to shutdown
				    m_flgStatus = ThreadStatus.Shutdown;
			    }
		    }

		    //check if the stopping timeout is 0 (or less)
		    if (0 >= numTimeout)	//no timeout specified?
		    {
			    //allow default waiting time if no timeout has been specified
			    for (int i = THREAD_STOP_COUNT; 0 < i; --i)
			    {
				    //switch threads and wait
                    Thread.Sleep(THREAD_STOP_SLEEP);
			    }

			    //thread stopping verification is not required
			    return true;
		    }
		    else
		    {
			    //wait for the thread to stop and verify its state
			    for (int i = numTimeout; 0 < i; --i)
			    {
				    //switch threads and wait
                    Thread.Sleep(THREAD_STOP_SLEEP);

				    //check if the thread has stopped
				    ThreadStatus status = GetStatus();
                    if ((ThreadStatus.Unknown == status) ||
                        (ThreadStatus.Stopped == status))
				    {
					    //thread has stopped
					    return true;
				    }
			    }
		    }

		    //failed to stop the thread
		    return false;
	    }
        #endregion

        #region Protected Methods
	    //virtual function - should be overriden
	    //(do NOT delete the CThread object within 
	    //this function or bad things will haoppen!)
	    protected virtual bool ThreadStart(threadclass objThread)
	    {
		    objThread = null;	//just to suppress a warning
		    return true;	//return "FALSE" if error during initialization
	    }

	    //virtual function - should be overriden
	    //(do NOT delete the CThread object within 
	    //this function or bad things will haoppen!)
	    protected virtual bool ThreadStop(threadclass objThread)
	    {
		    objThread = null;	//just to suppress a warning
		    return true;	//return "FALSE" to autodelete the thread (it makes
						    //sense only for dynamically created threads)
	    }					

	    //virtual function - should be overriden
	    //(do NOT delete the CThread object within 
	    //this function or bad things will happen!)
	    protected virtual bool ThreadProc(threadclass objThread)
	    {
		    objThread = null;	//just to suppress a warning
		    return true;	//return "FALSE" to stop the thread
	    }
        #endregion

        #region Private Methods
        private void ThreadMain(threadclass objThread)
	    {
            if(null == objThread)
            {
                //error
            }

		    //local data
		    bool started = false;
		    bool destroy = false;

		    //enter critical section
            lock(objThread.m_objThreadLock)
            {
			    //is the thread still marked as starting?
			    if (ThreadStatus.Starting == objThread.m_flgStatus)
			    {
				    //mark the thread as started
				    objThread.m_flgStatus = ThreadStatus.Started;
				    started = true;

				    //prepare thread
				    //Platform::PREPARE_THREAD(pthread->m_clsThread);
			    }
            }

		    //**************************************************
		    //thread initialization and processing
		    try
		    {
			    //thread started successfully?
			    if (false != started)
			    {
				    //execute the initialization code
				    if (false != objThread.ThreadStart(objThread))
				    {
					    //execute the main thread processing loop
					    while (ThreadStatus.Started == objThread.GetStatus())
					    {
						    //execute the processing code
                            if (false == objThread.ThreadProc(objThread))
                            {
                                //thread processing finished normally
                                break;
                            }

						    //switch threads
                            Thread.Sleep(THREAD_IDLE_SLEEP);
					    }
				    }
			    }
		    }
		    catch { throw; }

		    //**************************************************
		    //the thread is stopping
            lock(objThread.m_objThreadLock)
            {
			    //the thread has stopped
			    objThread.m_flgStatus = ThreadStatus.Stopping;
            }

		    //thread cleanup
		    try
		    {
			    //execute the cleanup code
			    if (false == objThread.ThreadStop(objThread))
			    {
				    //auto-delete this object
				    destroy = true;
			    }
		    }
		    catch
		    {
			    //unexpected exception happened
                throw;
		    }

		    //**************************************************
		    //the thread has stopped
            lock(objThread.m_objThreadLock)
            {
			    //cleanup after the thread is done
			    //Platform::CLEANUP_THREAD(pthread->m_clsThread);

			    //the thread has stopped
			    objThread.m_clsThread = null;
			    objThread.m_flgStatus = ThreadStatus.Stopped;
            }

		    //auto delete this object?
		    if (false != destroy)
		    {
			    //auto-delete the thread object
			    //delete pthread;
		    }

		    //exit this thread
		    return;
	    }

	    private void ThreadShut(threadclass objThread)
	    {
            if(null == objThread)
            {
                //error
            }

		    //stop the thread
		    try 
		    {
			    //try stopping the thread asynchronously
			    if (false == objThread.Stop(0))
			    {
				    //the thread failed to stop
			    }
		    }
            catch { throw; }

		    //exit this thread
		    return;
	    }
        #endregion
    }

    public abstract class thd_ipbaseclass : threadclass
    {
        #region Variables
        private ipsocket _ipsocket        = null;
        private object   _tag             = null;
        private object   _owner           = null;
        private object   _timeoutlock     = null;
        private int      _readidletimeout = 0; // [s]
        private int      _sendidletimeout = 0; // [s]
        #endregion

        #region Constructor
        public thd_ipbaseclass()
        {
            _timeoutlock = new object();
            _ipsocket = new ipsocket();
            _ipsocket.ExceptionEvent += new EventHandler<ExceptionEventArgs>(_ipsocket_ExceptionEvent);
        }

        ~thd_ipbaseclass()
        {
            //make sure to call thd_ipbaseclass::Shutdown(...) 
            //from the destructor of the derived class
            _ipsocket.ExceptionEvent -= new EventHandler<ExceptionEventArgs>(_ipsocket_ExceptionEvent);
        }
        #endregion

        #region Properties
        public ipsocket ipSocket
        {
            get { return (_ipsocket); }
            set { _ipsocket = value; }
        }

        public object Tag
        {
            get { return (_tag); }
            set { _tag = value; }
        }

        public object Owner
        {
            get { return (_owner); }
            set { _owner = value; }
        }

        public int ReadIdleTimeout
        {
            get { lock (_timeoutlock) { return (_readidletimeout); } }
            set { lock (_timeoutlock) { _readidletimeout = ((value > 0) ? value : 0); } }
        }

        public int SendIdleTimeout
        {
            get { lock (_timeoutlock) { return (_sendidletimeout); } }
            set { lock (_timeoutlock) { _sendidletimeout = ((value > 0) ? value : 0); } }
        }
        #endregion

        #region Public Methods
        public virtual bool Activate()
        {
            //start the thread
            if (false != base.Start())
            {
                //success
                return true;
            }

            //make sure everything is shutdown
            Shutdown(threadclass.THREAD_STOP_COUNT);
            return false;
        }

        public virtual bool Shutdown(int numTimeout)
        {
            //stop the thread
            if (false == base.Stop(numTimeout))
            {
                //the thread hasn't stopped yet
                return false;
            }

            //check the socket
            if (null != _ipsocket)
            {
                //shutdown and close the socket
                try { _ipsocket.Shutdown(SocketShutdown.Both); }
                catch { }
                try { _ipsocket.Close(); }
                catch { }
            }

            //done
            return true;
        }

        public virtual bool IsActive()
        {
            ThreadStatus status = base.GetStatus();
            return (((ThreadStatus.Unknown != status) &&
                (ThreadStatus.Stopped != status)) ? true : false);
        }
        #endregion

        #region Protected Methods
        protected bool GetLocalAddress(ref AddressInfo info)
        {
            try
            {
                if (info != null)
                {
                    info.Clear();
                    if (_ipsocket.socket != null)
                    {
                        return (_ipsocket.GetLocalHost(ref info.Family, ref info.Address, ref info.Port));
                    } // if
                } // if
            }
            catch(Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } //  try

            return (false);
        }

        protected bool GetRemoteAddress(ref AddressInfo info)
        {
            try
            {
                if (info != null)
                {
                    info.Clear();
                    if (_ipsocket.socket != null)
                    {
                        return (_ipsocket.GetRemoteHost(ref info.Family, ref info.Address, ref info.Port));
                    } // if
                } // if
            }
            catch (Exception e)
            {
                OnExceptionEvent(this, new ExceptionEventArgs(e));
            } // try

            return (false);
        }

        protected new ThreadStatus GetStatus()
        {
            return base.GetStatus();
        }

        protected SocketStatus Poll(SocketQuery flgQuery)
        {
	        //check the socket
	        if (null != _ipsocket)
	        {
		        //query the socket
                return _ipsocket.Query(flgQuery, 1);
	        }

	        //failure
	        return SocketStatus.IS_FAILURE;
        }
        #endregion

        #region Events
        public event EventHandler<ExceptionEventArgs> ExceptionEvent;

        private void _ipsocket_ExceptionEvent(object sender, ExceptionEventArgs e)
        {
            // forward ipsocket level exception event
            OnExceptionEvent(sender, e);
        }

        protected void OnExceptionEvent(object sender, ExceptionEventArgs e)
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
        #endregion
    }

    public class UDPPoint : thd_ipbaseclass
    { 
        #region Constants
        private const int POINT_SEND_WAIT   = 10;	//[ms]
        private const int POINT_READ_WAIT   = 1;	//[ms]
        private const int POINT_MAX_BUFSIZE = 8200;
        #endregion

        #region Variables
	    private AddressFamily m_flgFamily;
	    private AddressInfo   m_clsLocalAddress;
	    private AddressInfo   m_clsRemoteAddress;
	    private byte[]        m_bufRxData;
    	private DateTime      m_objReadIdleTimeout;
	    private DateTime      m_objSendIdleTimeout;
	    private object        m_objTimeoutLock;
        #endregion

        #region Constructor
        public UDPPoint(AddressFamily flgFamily = AddressFamily.InterNetwork)
        {
            m_flgFamily      = flgFamily;
            m_bufRxData      = new byte[POINT_MAX_BUFSIZE];
            m_objTimeoutLock = new object();
            m_clsLocalAddress = new AddressInfo();
            m_clsRemoteAddress = new AddressInfo();
            m_objReadIdleTimeout = new DateTime();
            m_objSendIdleTimeout = new DateTime();

            //reset timeouts
            ResetReadIdleTimeout();
            ResetSendIdleTimeout();
        }

        ~UDPPoint()
        {
	        //make sure to shutdown the thread first or 
	        //otherwise bad things will happen!
	        base.Shutdown(threadclass.THREAD_STOP_COUNT);
        }
        #endregion

        #region Public Methods
        public bool Activate(string strAddr, int numPort)
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        try
	        {
		        //clear addresses
		        m_clsLocalAddress.Clear();
		        m_clsRemoteAddress.Clear();

		        //check if socket is already present
		        if (null != base.ipSocket.socket)
		        {
			        //socket must be closed first
			        return false;	//do not touch the socket here!
		        }

		        //create new socket
		        if (false == base.ipSocket.Create(
			        m_flgFamily, ProtocolType.Udp, false))
		        {
			        //cannot create a socket
			        goto Activate_Failure;
		        }
	
		        //try binding the socket
		        if (false == base.ipSocket.Bind(strAddr, numPort))
		        {
			        //cannot bind the socket
			        goto Activate_Failure;
		        }
	
		        //start the thread
		        if (false != base.Activate())
		        {
			        //success
			        return true;
		        }
	        }
	        catch{}

        Activate_Failure:

	        //close the socket and exit
	        base.Shutdown(THREAD_STOP_COUNT);
	        return false;
        }

        public int SendTo(AddressInfo refAddress, byte[] bufData, int numSize, int numTimeout) //timeout [s]
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return -1;
	        }

            //initialize variables
            int sent = 0;
            int total = 0;
            SocketStatus status;
	
	        //send data
	        DateTime timeout = ((0 < numTimeout) ? DateTime.Now.AddSeconds(numTimeout) : DateTime.MaxValue);
            while(0 >= DateTime.Compare(DateTime.Now, timeout))
            {
		        //check if ready to send
		        status = base.Poll(SocketQuery.QUERY_SEND);
		        if (SocketStatus.IS_SUCCESS == status)
		        {
			        //send data
			        try { sent = base.ipSocket.SendTo(refAddress.Address, refAddress.Port, bufData, (numSize - total), total); }
			        catch { sent = -1; }
			        if (0 <= sent)
			        {
				        //reset tx idle timeout
				        ResetSendIdleTimeout();

				        //count sent bytes
				        total += sent;
				        if (total >= numSize)
				        {
					        //all data sent
					        break;
				        }
			        } 
			        else
			        {
				        //failed to send data
				        break;
			        }
		        }
		        else if (SocketStatus.IS_FAILURE == status)
		        {
			        //stop trying to send data
			        break;
		        }
		        //switch threads and wait
		        Thread.Sleep(POINT_SEND_WAIT);
	        }

	        //return the total number of bytes sent
	        return total;
        }
        #endregion

        #region Private Methods
        protected override bool ThreadStart(threadclass objThread)
        {
	        //get address info
	        if (false == GetLocalAddress(ref m_clsLocalAddress))
	        {
		        //cannot get local or remote address
		        return false;
	        }

	        //reset timeouts
	        ResetReadIdleTimeout();
	        ResetSendIdleTimeout();

	        //prepare event args
            SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;
	        args.remoteaddress.Clear();

            //fire event
            try { ActivateEvent(this, args); } catch {}

	        //done!
	        return true;
        }

        protected override bool ThreadStop(threadclass objThread)
        {
	        //shutdown and close the socket
	        if (null != base.ipSocket)
	        {
		        try { base.ipSocket.Shutdown(SocketShutdown.Both); }
		        catch {}
		        try { base.ipSocket.Close(); }
		        catch {}
	        }

	        //prepare event args
            SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;
	        args.remoteaddress.Clear();

            //fire event
            try { ShutdownEvent(this, args); } catch {}
	        return true;
        }

        protected override bool ThreadProc(threadclass objThread)
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        //prepare event args
            SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;

	        //check if there is anything to read
	        SocketStatus status = base.Poll(SocketQuery.QUERY_READ);
	        if (SocketStatus.IS_SUCCESS == status)
	        {
		        //read data
                AddressInfo remote = new AddressInfo();
		        int read = 0;
                try
                {
                    try
                    {
                        read = base.ipSocket.ReadFrom(ref remote.Family, ref remote.Address, ref remote.Port, m_bufRxData, POINT_MAX_BUFSIZE);
                    }
                    catch (Exception)
                    {
                        read = -1;
                    }
                    if (0 < read)
                    {
                        //reset read idle timeout
                        ResetReadIdleTimeout();

                        //update remote address
                        args.remoteaddress = remote;

                        //allocate data buffer
                        args.databuffer = new byte[read];

                        //copy data
                        Array.Copy(m_bufRxData, 0, args.databuffer, 0, read);

                        //fire event
                        try { ReceivedEvent(this, args); }
                        catch { }
                    }
                }
                catch (SocketException se)
                {
                    if (0 != se.ErrorCode)
                    {
                        return false;
                    }
                }
	        }
	        else if (SocketStatus.IS_FAILURE == status)
	        {
		        //stop polling the socket
		        return false;	//end the thread
	        }
	        else	//SockStatuses::IS_TIMEOUT
	        {
		        //check read idle timeout
		        TestReadIdleTimeout();
		
		        //check send idle timeout
		        TestSendIdleTimeout();

		        //switch threads - take your time because there was no new data
		        Thread.Sleep(POINT_READ_WAIT);
	        }

	        //fire event
	        try { MainLoopEvent(this, args); } catch {}
	        return true;
        }

        private void ResetReadIdleTimeout()
        {
	        //reset rx idle timeout [s]
            lock(m_objTimeoutLock)
            {
    	        int timeout = base.ReadIdleTimeout;
	            m_objReadIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);
            }
        }

        private void ResetSendIdleTimeout()
        {
	        //reset tx idle timeout [s]
            lock(m_objTimeoutLock)
            {
    	        int timeout = base.SendIdleTimeout;
	            m_objSendIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);
            }
        }

        private void TestReadIdleTimeout()
        {
	        //check idle timeout
            lock(m_objTimeoutLock)
            {
	            if (0 <= DateTime.Compare(DateTime.Now, m_objReadIdleTimeout))
	            {
		            //reset rx idle timeout
		            int timeout = base.ReadIdleTimeout;
                    m_objReadIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);

		            //prepare event args
                    SocketEventArgs args = new SocketEventArgs();
		            args.localaddress = m_clsLocalAddress;
		            args.remoteaddress.Clear();

		            //signal idle
		            try { ReadIdleEvent(this, args); } catch {}
	            }
            }
        }

        private void TestSendIdleTimeout()
        {
	        //check idle timeout
            lock(m_objTimeoutLock)
            {
	            if (0 <= DateTime.Compare(DateTime.Now, m_objSendIdleTimeout))
	            {
		            //reset rx idle timeout
		            int timeout = base.SendIdleTimeout;
		            m_objSendIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);

		            //prepare event args
                    SocketEventArgs args = new SocketEventArgs();
		            args.localaddress = m_clsLocalAddress;
		            args.remoteaddress.Clear();

		            //signal idle
		            try { SendIdleEvent(this, args); } catch {}
	            }
            }
        }
        #endregion

        #region Events
        public event EventHandler<SocketEventArgs> ActivateEvent;
        public event EventHandler<SocketEventArgs> ShutdownEvent;
        public event EventHandler<SocketEventArgs> MainLoopEvent;
        public event EventHandler<SocketEventArgs> ReadIdleEvent;
        public event EventHandler<SocketEventArgs> SendIdleEvent;
        public event EventHandler<SocketEventArgs> ReceivedEvent;
        #endregion
    }

    public class TCPProxy : thd_ipbaseclass
    {
        #region Constants
        private const int PROXY_SEND_WAIT = 10;	//[ms]
        private const int PROXY_READ_WAIT = 1;	//[ms]
        private const int PROXY_MAX_BUFSIZE = 8200;
        #endregion

        #region Variables
    	private AddressInfo		m_clsLocalAddress;
    	private AddressInfo		m_clsRemoteAddress;
    	private byte[]			m_bufRxData;
    	private DateTime		m_objReadIdleTimeout;
    	private DateTime		m_objSendIdleTimeout;
    	private object      	m_objTimeoutLock;
        #endregion

        #region Constructor
        public TCPProxy()
        {
            m_bufRxData      = new byte[PROXY_MAX_BUFSIZE];
            m_objTimeoutLock = new object();
            m_clsLocalAddress = new AddressInfo();
            m_clsRemoteAddress = new AddressInfo();
            m_objReadIdleTimeout = new DateTime();
            m_objSendIdleTimeout = new DateTime();

            //reset timeouts
            ResetReadIdleTimeout();
            ResetSendIdleTimeout();
        }

        ~TCPProxy()
        {
        	//make sure to shutdown the thread first or 
	        //otherwise bad things will happen!
	        base.Shutdown(threadclass.THREAD_STOP_COUNT);
        }
        #endregion

        #region Public Methods
        public new bool Activate()
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        try
	        {
		        //clear addresses
		        m_clsLocalAddress.Clear();
		        m_clsRemoteAddress.Clear();

		        //check if socket is already present
		        if (null == base.ipSocket.socket)
		        {
			        //socket must be present
			        return false;
		        }

		        //start the thread
		        if (false != base.Activate())
		        {
			        //success
			        return true;
		        }
	        }
	        catch {}

	        //make sure the proxy is shutdown
	        base.Shutdown(threadclass.THREAD_STOP_COUNT);
            return false;
        }

        public int Send(byte[] bufData, int numSize, int numTimeout) // [s]
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return (-1);
	        }

            //initialize variables
            int sent = 0;
            int total = 0;
            SocketStatus status;
	
	        //send data
	        DateTime timeout = ((0 < numTimeout) ? DateTime.Now.AddSeconds(numTimeout) : DateTime.MaxValue);
	        while (0 >= DateTime.Compare(DateTime.Now, timeout))
	        {
		        //check if ready to send
		        status = base.Poll(SocketQuery.QUERY_SEND);
		        if (SocketStatus.IS_SUCCESS == status)
		        {
			        //send data
			        try { sent = base.ipSocket.Send(bufData, (numSize - total), total); }
			        catch { sent = -1; }
			        if (0 <= sent)
			        {
				        //reset tx idle timeout
				        ResetSendIdleTimeout();

				        //count sent bytes
				        total += sent;
				        if (total >= numSize)
				        {
					        //all data sent
					        break;
				        }
			        } 
			        else
			        {
				        //failed to send data
				        break;
			        }
		        }
		        else if (SocketStatus.IS_FAILURE == status)
		        {
			        //stop trying to send data
			        break;
		        }
		        //switch threads and wait
		        Thread.Sleep(PROXY_SEND_WAIT);
	        }

	        //return the total number of bytes sent
	        return total;
        }

        public override bool Shutdown(int numTimeout)
        {
            return (base.Shutdown(numTimeout));
        }
        #endregion

        #region Private Methods
        protected override bool ThreadStart(threadclass objThread)
        {
	        //get address info
	        if ((false == base.GetLocalAddress(ref m_clsLocalAddress)) ||
		        (false == base.GetRemoteAddress(ref m_clsRemoteAddress)))
	        {
		        //cannot get local or remote address
		        return false;
	        }

	        //reset timeouts
	        ResetReadIdleTimeout();
	        ResetSendIdleTimeout();

	        //prepare event args
	        SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;
	        args.remoteaddress = m_clsRemoteAddress;

            //fire event
            try { ActivateEvent(this, args); } catch {}

	        //done!
	        return true;
        }

        protected override bool ThreadStop(threadclass objThread)
        {
	        //shutdown and close the socket
	        if (null != base.ipSocket)
	        {
		        try { ipSocket.Shutdown(SocketShutdown.Both); }
		        catch {}
		        try { ipSocket.Close(); }
		        catch {}
	        }

	        //prepare event args
	        SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;
	        args.remoteaddress = m_clsRemoteAddress;

            //fire event
            try { ShutdownEvent(this, args); } catch {}
	        return true;
        }

        protected override bool ThreadProc(threadclass objThread)
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

            //prepare event args
            SocketEventArgs args = new SocketEventArgs();
            args.localaddress = m_clsLocalAddress;
            args.remoteaddress = m_clsRemoteAddress;

            //check if there is anything to read
            SocketStatus status = base.Poll(SocketQuery.QUERY_READ);
            if (SocketStatus.IS_SUCCESS == status)
            {
                //read data
                int read = 0;
                try
                {
                    try
                    {
                        read = base.ipSocket.Read(m_bufRxData, PROXY_MAX_BUFSIZE);
                    }
                    catch (Exception)
                    {
                        read = -1;
                    }
                    if (0 < read)
                    {
                        try
                        {
                            //reset read idle timeout
                            ResetReadIdleTimeout();

                            //allocate data buffer
                            args.databuffer = new byte[read];

                            //copy data
                            Array.Copy(m_bufRxData, 0, args.databuffer, 0, read);
                        }
                        catch { throw; }

                        //fire event
                        try { ReceivedEvent(this, args); }
                        catch { throw; }
                    }
                    else
                    {
                        //socket error or connection closed
                        return false;	//end the thread
                    }
                }
                catch (SocketException se)
                {
                    if (0 != se.ErrorCode)
                    {
                        return false;
                    }
                }
            }
            else if (SocketStatus.IS_FAILURE == status)
            {
                //stop polling the socket
                return false;	//end the thread
            }
            else	//SockStatuses::IS_TIMEOUT
            {
                //check read idle timeout
                TestReadIdleTimeout();

                //check send idle timeout
                TestSendIdleTimeout();

                //switch threads - take your time because there was no new data
                Thread.Sleep(PROXY_READ_WAIT);
            }

	        //fire event
            try { MainLoopEvent(this, args); }
            catch { throw; }
	        return true;
        }

        private void ResetReadIdleTimeout()
        {
            //reset rx idle timeout [s]
            lock (m_objTimeoutLock)
            {
                int timeout = base.ReadIdleTimeout;
                m_objReadIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);
            }
        }

        private void ResetSendIdleTimeout()
        {
            //reset tx idle timeout [s]
            lock (m_objTimeoutLock)
            {
                int timeout = base.SendIdleTimeout;
                m_objSendIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);
            }
        }

        private void TestReadIdleTimeout()
        {
            //check idle timeout
            lock (m_objTimeoutLock)
            {
                if (0 <= DateTime.Compare(DateTime.Now, m_objReadIdleTimeout))
                {
                    //reset rx idle timeout
                    int timeout = base.ReadIdleTimeout;
                    m_objReadIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);

                    //prepare event args
                    SocketEventArgs args = new SocketEventArgs();
                    args.localaddress = m_clsLocalAddress;
                    args.remoteaddress = m_clsRemoteAddress;

                    //signal idle
                    try { ReadIdleEvent(this, args); }
                    catch { }
                }
            }
        }

        private void TestSendIdleTimeout()
        {
            //check idle timeout
            lock (m_objTimeoutLock)
            {
                if (0 <= DateTime.Compare(DateTime.Now, m_objSendIdleTimeout))
                {
                    //reset rx idle timeout
                    int timeout = base.SendIdleTimeout;
                    m_objSendIdleTimeout = ((0 < timeout) ? DateTime.Now.AddSeconds(timeout) : DateTime.MaxValue);

                    //prepare event args
                    SocketEventArgs args = new SocketEventArgs();
                    args.localaddress = m_clsLocalAddress;
                    args.remoteaddress = m_clsRemoteAddress;

                    //signal idle
                    try { SendIdleEvent(this, args); }
                    catch { }
                }
            }
        }
        #endregion

        #region Events
        public event EventHandler<SocketEventArgs> ActivateEvent;
        public event EventHandler<SocketEventArgs> ShutdownEvent;
        public event EventHandler<SocketEventArgs> MainLoopEvent;
        public event EventHandler<SocketEventArgs> ReadIdleEvent;
        public event EventHandler<SocketEventArgs> SendIdleEvent;
        public event EventHandler<SocketEventArgs> ReceivedEvent;
        #endregion
    }

    public class TCPClient : TCPProxy
    {
        #region Constants
        private const int CLIENT_CONNECT_WAIT = 10;	//[ms]
        #endregion

        #region Variables
        private AddressFamily m_flgFamily;
        #endregion

        #region Constructor
        public TCPClient(AddressFamily flgFamily = AddressFamily.InterNetwork)
        {
            m_flgFamily = flgFamily;
        }

        ~TCPClient()
        {
        }
        #endregion

        #region Public Methods
        public bool Connect(string address, int port, int numTimeout) //[s]
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        try
	        {
		        //check if socket is already present
		        if (null != base.ipSocket.socket)
		        {
			        //socket must be closed first
			        return false;	//do not touch the socket here!
		        }

		        //create new non-blocking socket
		        if (false == base.ipSocket.Create(m_flgFamily, ProtocolType.Tcp, true))
		        {
			        //cannot create a socket
			        goto Connect_Failure;
		        }
	
		        //try connecting
		        bool connected = false;
                try
                {
                    if(false != base.ipSocket.Connect(address, port))
                    {
                        //connected
                        connected = true;
                    }
                }
                catch(SocketException se)
                {
                    if(se.SocketErrorCode == SocketError.WouldBlock)
                    {
                        //calculate timeout
                        DateTime timeout = ((0 < numTimeout) ? DateTime.Now.AddSeconds(numTimeout) : DateTime.MaxValue);
                        while(0 >= DateTime.Compare(DateTime.Now, timeout))
                        {
					        //check if connected
					        if (SocketStatus.IS_SUCCESS == 
						        base.Poll(SocketQuery.QUERY_CONNECT))
					        {
						        //connected
						        connected = true;
						        break;
					        }
				
					        //switch threads and wait
					        Thread.Sleep(CLIENT_CONNECT_WAIT);
                        }
                    }
                }
		        //check if client is connected
		        if (false != connected)
		        {
			        //change socket to blocking
			        if (false != base.ipSocket.SetBlocking(true))
			        {
				        //start thread
				        return base.Activate();
			        }
		        }
	        }
	        catch (Exception)
	        {
		        //do nothing
	        }

        Connect_Failure:

	        //close the socket and exit
	        base.Shutdown(threadclass.THREAD_STOP_COUNT);
	        return false;
        }
        #endregion
    }

    public class TCPServer : TCPProxy
    {
        #region Constants
        private const int SERVER_THREAD_WAIT = 1; //[ms]
        private const int SERVER_ACCEPT_WAIT = 1; //[ms]
        private const int SERVER_CLIENT_TIMEOUT = 3; //[sec] (longer than THREAD_STOP_COUNT * THREAD_STOP_SLEEP)
        #endregion

        #region Variables
        private AddressFamily m_flgFamily;
        private AddressInfo m_clsLocalAddress;
        private object m_objClientsLock;
        private Dictionary<TCPProxy, TCPProxy> m_lstClients;
        private List<TCPProxy> m_lstZombies;	//proxies that are no longer active
        #endregion

        #region Constructor
        public TCPServer(AddressFamily flgFamily = AddressFamily.InterNetwork)
        {
            m_flgFamily = flgFamily;
            m_objClientsLock = new object();
            m_clsLocalAddress = new AddressInfo();
            m_lstClients = new Dictionary<TCPProxy, TCPProxy>();
            m_lstZombies = new List<TCPProxy>();
        }

        ~TCPServer()
        {
            //make sure to shutdown the thread first or 
            //otherwise bad things will happen!
            this.Shutdown();
        }
        #endregion

        #region Public Methods
        public bool Activate(string address, int port)
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        try
	        {
		        //check if socket is already present
		        if (null != base.ipSocket.socket)
		        {
			        //socket must be closed first
			        return false;	//do not touch the socket here!
		        }

		        //create new non-blocking socket
		        if (false == base.ipSocket.Create(
			        m_flgFamily, ProtocolType.Tcp, true))
		        {
			        //cannot create a socket
			        goto Activate_Failure;
		        }
	
		        //try binding new socket
		        if (false == base.ipSocket.Bind(address, port))
		        {
			        //cannot bind
			        goto Activate_Failure;
		        }
	
		        //start the therad
		        if (false != base.Activate())
		        {
			        //success
			        return true;
		        }
	        }
	        catch {}

        Activate_Failure:

	        //make sure the server is shutdown
	        base.Shutdown(threadclass.THREAD_STOP_COUNT);
	        return false;
        }

        public void Shutdown()
        {
	        //try to shutdown the server thread
	        while (false == base.Shutdown(threadclass.THREAD_STOP_COUNT))
	        {
		        //wait until all proxies shut down, etc.
		        Thread.Sleep(threadclass.THREAD_STOP_SLEEP);
	        }
        }

        public void ShutProxy(TCPProxy proxy)
        {
	        //find the proxy on the list
            lock(m_objClientsLock)
            {
	            bool present = m_lstClients.ContainsKey(proxy);
	            if (false != present)	//is proxy still present?
	            {
		            //shutdown the proxy asynchronously
		            try { proxy.Shutdown(0); } catch {}
	            }
            }
        }

        protected override bool ThreadStart(threadclass objThread)
        {
            //fire event
            try { ActivateEvent(this, null); } catch {}

	        //get address info
	        if (false == base.GetLocalAddress(ref m_clsLocalAddress))
	        {
		        //cannot get local address
		        return false;
	        }

	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        //start listening
	        return base.ipSocket.Listen();
        }

        protected override bool ThreadStop(threadclass objThread)
        {
	        //shutdown and close the socket
	        if (null != base.ipSocket)
	        {
		        try { base.ipSocket.Shutdown(SocketShutdown.Both); }
		        catch {}
		        try { base.ipSocket.Close(); }
		        catch {}
	        }

	        //shutdown and delete all active clients
            lock(m_objClientsLock)
            {
		        for (int i = m_lstClients.Count(); 0 < i; --i)
		        {
			        //do casting magic to get the proxy pointer without 
			        //removing it from the list of clients
                    KeyValuePair<TCPProxy, TCPProxy> kvpClient = m_lstClients.ElementAt(i - 1);
                    TCPProxy client = kvpClient.Value;
                    client.Shutdown(0); //do not wait for the thread to stop
		        }
            }

	        //wait for all clients to close
	        DateTime timeout = DateTime.Now.AddSeconds(SERVER_CLIENT_TIMEOUT);
	        int closing = 0;
	        while (0 >= DateTime.Compare(DateTime.Now, timeout))
	        {
		        //check if clients are gone
                lock(m_objClientsLock)
                {
			        int count = m_lstClients.Count();
			        if (0 == count)
			        {
				        //all clients are gone
				        break;
			        }
			        else if (closing != count)
			        {
				        //extend the timeout as long as the clients keep closing
				        closing = count;
				        timeout = DateTime.Now.AddSeconds(SERVER_CLIENT_TIMEOUT);
			        }
                }

		        //switch threads
		        Thread.Sleep(threadclass.THREAD_STOP_SLEEP);
	        }

	        //delete all zombies
            lock(m_objClientsLock)
            {
		        m_lstZombies.Clear();
            }

	        //prepare event args
	        SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;

            //fire event
            try { ShutdownEvent(this, args); } catch {}
	        return true;
        }

        protected override bool ThreadProc(threadclass objThread)
        {
	        //sanity check
	        if (null == base.ipSocket)
	        {
		        return false;
	        }

	        //prepare event args
	        SocketEventArgs args = new SocketEventArgs();
	        args.localaddress = m_clsLocalAddress;

	        //check if there is any incomming connection ready
	        SocketStatus status = base.Poll(SocketQuery.QUERY_ACCEPT);
	        if (SocketStatus.IS_SUCCESS == status)
	        {
		        //client address info
		        AddressInfo addr = new AddressInfo();

		        //create new client proxy
		        TCPProxy proxy = new TCPProxy();
			        
                //setup proxy and connect events
                proxy.ReadIdleTimeout = base.ReadIdleTimeout;
                proxy.SendIdleTimeout = base.SendIdleTimeout;
			    ConnectEvents(proxy);

			    //accept new connection
			    try 
			    { 
				    //try accepting the socket
				    if (false != base.ipSocket.Accept(proxy.ipSocket, 
					    ref addr.Family, ref addr.Address, ref addr.Port))
				    {
					    //After accepting the connection, the proxy must be 
					    //1) added to the list of clients, and 2) activated.
					    //The order of those 2 operations matter! - If the proxy
					    //was activated first, the event OnConnectionClosedEvent 
					    //might fire before the proxy is added to the list - and 
					    //then the already inactive proxy would have been added 
					    //to the list permannently because OnConnectionClosedEvent 
					    //would never fire again for such a 'zombie' proxy!
					    //Moreover, any new proxy created within the same memory 
					    //block (which is very likely!) couldn't be added to the 
					    //list because of the same key as the 'zombie' proxy.
					    //Therefore it is important to add proxy to the list first
					    //and then try to activate it - to guarantee its later
					    //removal from the list by the OnConnectionClosedEvent.

					    //add new proxy to the list
                        lock(m_objClientsLock)
                        {
					        m_lstClients.Add(proxy, proxy);
						    //activate new proxy
						    if (false == proxy.Activate())
						    {
							    //activation failed
							    //remove the proxy container from the list
							    m_lstClients.Remove(proxy);
                			    DisconnectEvents(proxy);
						    }
                        }
				    }
                    else
                    {
			            DisconnectEvents(proxy);
                    }
			    }
			    catch 
			    {
	    		    DisconnectEvents(proxy);
			    }
	        }
	        else if (SocketStatus.IS_FAILURE == status)
	        {
		        //stop polling the socket
		        return false;	//end the thread
	        }
	        else	//SockStatuses::IS_TIMEOUT
	        {
		        //delete all zombies
                lock(m_objClientsLock)
                {
		            m_lstZombies.Clear();
                }

		        //switch threads
		        Thread.Sleep(SERVER_THREAD_WAIT);
	        }

	        //fire event
	        try { MainLoopEvent(this, args); } catch {}
	        return true;
        }

        private void ConnectEvents(TCPProxy proxy)
        {
	        if (null != proxy)
	        {
                proxy.Owner = this;
                proxy.ActivateEvent += new EventHandler<SocketEventArgs>(proxy_OnConnectionOpen);
                proxy.ShutdownEvent += new EventHandler<SocketEventArgs>(proxy_OnConnectionClosed);
                proxy.MainLoopEvent += new EventHandler<SocketEventArgs>(proxy_OnConnectionThread);
                proxy.ReadIdleEvent += new EventHandler<SocketEventArgs>(proxy_OnConnectionRxIdle);
                proxy.SendIdleEvent += new EventHandler<SocketEventArgs>(proxy_OnConnectionTxIdle);
                proxy.ReceivedEvent += new EventHandler<SocketEventArgs>(proxy_OnConnectionRxData);
	        }
        }

        private void DisconnectEvents(TCPProxy proxy)
        {
	        if (null != proxy)
	        {
                proxy.ActivateEvent -= new EventHandler<SocketEventArgs>(proxy_OnConnectionOpen);
                proxy.ShutdownEvent -= new EventHandler<SocketEventArgs>(proxy_OnConnectionClosed);
                proxy.MainLoopEvent -= new EventHandler<SocketEventArgs>(proxy_OnConnectionThread);
                proxy.ReadIdleEvent -= new EventHandler<SocketEventArgs>(proxy_OnConnectionRxIdle);
                proxy.SendIdleEvent -= new EventHandler<SocketEventArgs>(proxy_OnConnectionTxIdle);
                proxy.ReceivedEvent -= new EventHandler<SocketEventArgs>(proxy_OnConnectionRxData);
                proxy.Owner = null;
	        }
        }
        #endregion

        #region Events
        public new event EventHandler<SocketEventArgs> ActivateEvent;
        public new event EventHandler<SocketEventArgs> ShutdownEvent;
        public new event EventHandler<SocketEventArgs> MainLoopEvent;
        public event EventHandler<SocketEventArgs> ConnectionOpenEvent;
        public event EventHandler<SocketEventArgs> ConnectionClosedEvent;
        public event EventHandler<SocketEventArgs> ConnectionThreadEvent;
        public event EventHandler<SocketEventArgs> ConnectionRxIdleEvent;
        public event EventHandler<SocketEventArgs> ConnectionTxIdleEvent;
        public event EventHandler<SocketEventArgs> ConnectionRxDataEvent;

        private void proxy_OnConnectionOpen(object sender, SocketEventArgs args)
        {
        	//fire event
	        try { ConnectionOpenEvent(sender, args); } catch {}
        }

        private void proxy_OnConnectionClosed(object sender, SocketEventArgs args)
        {
	        //fire event
	        try { ConnectionClosedEvent(sender, args); } catch {}

	        //post-processing
	        if (null != sender)
	        {
		        //disconnect events
		        DisconnectEvents((sender as TCPProxy));

		        //move the proxy pointer (TMemPtr's operator= does that) from the
		        //clients list to the zombies list to avoid deleting the proxy here
                lock(m_objClientsLock)
                {
		            m_lstZombies.Add(m_lstClients[(sender as TCPProxy)]);
                    if (m_lstClients.ContainsKey((sender as TCPProxy)) == true)
                    {
                        m_lstClients.Remove((sender as TCPProxy));	//the proxy won't be deleted now
                    }
                }
	        }
        }

        private void proxy_OnConnectionThread(object sender, SocketEventArgs args)
        {
        	//fire event
	        try { ConnectionThreadEvent(sender, args); } catch {}
        }

        private void proxy_OnConnectionRxIdle(object sender, SocketEventArgs args)
        {
        	//fire event
        	try { ConnectionRxIdleEvent(sender, args); } catch {}
        }

        private void proxy_OnConnectionTxIdle(object sender, SocketEventArgs args)
        {
            //fire event
        	try { ConnectionTxIdleEvent(sender, args); } catch {}
        }

        private void proxy_OnConnectionRxData(object sender, SocketEventArgs args)
        {
            //fire event
        	try { ConnectionRxDataEvent(sender, args); } catch {}
        }
        #endregion
    }
    #endregion
}
