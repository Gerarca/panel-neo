using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.Diagnostics;
using TSP.DSC_InteractiveSDK;

namespace NET_TestApp
{
    public enum SessionTypes : int { NONE = 0, TCP, UDP };

    public class SessionKey
    {
        #region Variables
        private bool         _flgDisposed = false;
        public  SessionTypes sessiontype  = SessionTypes.NONE;
        public  AddressInfo  peeraddress  = new AddressInfo();
        #endregion

        #region Constructor
        public SessionKey()
        {
        }

        public SessionKey(SessionTypes type, AddressInfo address)
        {
            Clear();
            sessiontype = type;
            peeraddress = address;
        }

        public SessionKey(SessionKey other)
        {
            Clear();
            sessiontype = other.sessiontype;
            peeraddress = other.peeraddress;
        }

        ~SessionKey()
        {
            Dispose(false);
        }
        #endregion

        #region Public Methods
        public void Clear()
        {
            sessiontype = SessionTypes.NONE;
            peeraddress.Clear();
        }

        public static bool operator ==(SessionKey left, SessionKey right)
        {
            return (left.Equals(right));
        }

        public static bool operator !=(SessionKey left, SessionKey right)
        {
            return (!(left.Equals(right)));
        }

        public static bool operator >(SessionKey left, SessionKey right)
        {
            if (left.sessiontype > right.sessiontype)
            {
                return (true);
            } // if

            if (left.peeraddress > right.peeraddress)
            {
                return (true);
            } // if

            return (false);
        }

        public static bool operator <(SessionKey left, SessionKey right)
        {
            if (left.sessiontype < right.sessiontype)
            {
                return (true);
            } // if

            if (left.peeraddress < right.peeraddress)
            {
                return (true);
            } // if

            return (false);
        }

        public override bool Equals(object obj)
        {
            SessionKey other = (obj as SessionKey);

            if (object.ReferenceEquals(other, null) == true)
            {
                return (false);
            } // if

            if ((this.sessiontype == other.sessiontype) && (this.peeraddress.Equals(other.peeraddress)))
            {
                return (true);
            } // if

            return (false);
        }

        public override int GetHashCode()
        {
            string hash_string = this.sessiontype.ToString() + this.peeraddress.GetHashCode();

            return (hash_string.GetHashCode());
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

        #region Private Methods
        private void Dispose(bool flgDisposing)
        {
            //check if the object has already been disposed of
            if (_flgDisposed) return;

            //explicit disposing?
            if (flgDisposing)
            {
                //dispose of the managed resources
                //...
            }

            //dispose of the unmanaged resources
            //...

            //the object has been disposed of
            _flgDisposed = true;
        }
        #endregion
    }

    public class SessionData
    {
        #region Variables
        private bool                 _flgDisposed = false;
        private object               _lock        = new object();
        private UInt32               _systicks    = 0;
        private UInt32               _idletime    = 0;
        private DateTime             _idletimer   = DateTime.MinValue;
        private AddressInfo          _peeraddress = new AddressInfo();
        private TCPProxy             _tcpproxy    = null;
        private UDPPoint             _udppoint    = null;
        private IChannel             _channel     = null;
        #endregion

        #region Constructor
        public SessionData()
        {
        }

        public SessionData(SessionData other)
        {
            Clear();
            lock (_lock)
            {
                SysTicks    = other.SysTicks;
                IdleTime    = other.IdleTime;
                PeerAddress = other.PeerAddress;
                TCPProxy    = other.TCPProxy;
                UDPPoint    = other.UDPPoint;
                Channel     = other.Channel;
            } // lock
        }

        ~SessionData()
        {
            Dispose(false);
        }
        #endregion

        #region Properties
        public UInt32 SysTicks
        {
            get { lock (_lock) { return (_systicks); } }
            set { lock (_lock) { _systicks = value; } }
        }

        public UInt32 IdleTime
        {
            get { lock (_lock) { return (_idletime); } }
            set 
            { 
                lock (_lock) 
                { 
                    _idletime = value; 
                    _idletimer = ((0 < _idletime) ? DateTime.Now.AddSeconds((double)(_idletime)) : DateTime.MinValue); 
                } 
            }
        }

        public AddressInfo PeerAddress
        {
            get { lock (_lock) { return (_peeraddress); } }
            set { lock (_lock) { _peeraddress = value; } }
        }

        public TCPProxy TCPProxy
        {
            get { lock (_lock) { return (_tcpproxy); } }
            set { lock (_lock) { _tcpproxy = value; } }
        }

        public UDPPoint UDPPoint
        {
            get { lock (_lock) { return (_udppoint); } }
            set { lock (_lock) { _udppoint = value; } }
        }

        public IChannel Channel
        {
            get { lock (_lock) { return (_channel); } }
            set { lock (_lock) { _channel = value; } }
        }
        #endregion

        #region Public Methods
        public void Clear()
        {
            lock (_lock)
            {
                _systicks = 0;
                _idletime = 0;
                _idletimer = DateTime.MinValue;
                _peeraddress.Clear();
                _tcpproxy = null;
                _udppoint = null;
                _channel  = null;
            } // lock
        }

        public bool TestSysTicks()
        {
            lock(_lock)
            {
                if (0 < _systicks)
                {
                    if (0 < --_systicks)
                    {
                        return (false);
                    } // if
                } // if
                return(true);
            } // lock
        }

        public bool TestIdleTime()
        {
            lock (_lock)
            {
                if (0 < _idletime)
                {
                    //initialize first?
                    if (DateTime.MinValue == _idletimer)
                    {
                        //init the timeout
                        _idletimer = ((0 < _idletime) ? DateTime.Now.AddSeconds((double)(_idletime)) : DateTime.MinValue);
                    }
                    else if (DateTime.Now >= _idletimer)
                    {
                        //reset the timeout
                        _idletimer = ((0 < _idletime) ? DateTime.Now.AddSeconds((double)(_idletime)) : DateTime.MinValue);

                        //timeout reached
                        return (true);
                    }
                }
                return (false);
            } // lock
        }

        public void Dispose()
        {
            Dispose(true);
            GC.SuppressFinalize(this);
        }
        #endregion

        #region Private Methods
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
        #endregion
    }

    public class SessionKeyComparer : IComparer<SessionKey>
    {
        public SessionKeyComparer()
        {
        }

        public int Compare(SessionKey left, SessionKey right)
        {
            if (left > right)
            {
                return (1);
            }
            else if (left < right)
            {
                return (-1);
            } // if

            return (0);
        }
    }
}
