# TCPServerClientAPP
A simple TCP server and client app on C++ using Qt Framework created for personal educational purposes<br> 

📋 Core Features<br>
### Server:<br>
  **Implemented Features:**<br>
    ✅ Listens for incoming TCP connections<br>
    ✅ Receives and processes UTF-8 text messages<br>
    ✅ Sends echo responses fo clients<br>
    ✅ Tracks client connections and disconnections<br>
  **Not yet Implemented Features:**<br>
    ❌ Handles multiple clients simultaneously (currently single-client only)<br>
    ❌ Package checksum validation<br>
    ❌ Receives packages over a certain protocol<br>
  <br>
### Client:<br>
  **Implemented Features:**<br>
    ✅ Connects to TCP server<br>
    ✅ Sends text UTF-8 messages in bytes<br>
    ✅ Receives server responses<br>
  **Not yet Implemented Features:**<br>
    ❌ Network error handling<br>
    ❌ Sends packages over a structured protocol<br>
    ❌ Auto-reconnection capability<br>
