# TCPServerClientAPP
A simple TCP server and client app on C++ using Qt Framework created for personal educational purposes 

📋 Core Features
### Server:
  **Implemented Features:**
    ✅ Listens for incoming TCP connections
    ✅ Receives and processes UTF-8 text messages
    ✅ Sends echo responses fo clients
    ✅ Tracks client connections and disconnections
  **Not yet Implemented Features:**
    ❌ Handles multiple clients simultaneously (currently single-client only)
    ❌ Package checksum validation
    ❌ Receives packages over a certain protocol
  
### Client:
  **Implemented Features:**
    ✅ Connects to TCP server
    ✅ Sends text UTF-8 messages in bytes
    ✅ Receives server responses
  **Not yet Implemented Features:**
    ❌ Network error handling
    ❌ Sends packages over a structured protocol
    ❌ Auto-reconnection capability
