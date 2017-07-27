# EsotericVisage
Stealth remote administration tool 
```javascript
+-------+
| Local |
+-------+

[EV-Installer] --+
                 | - Determine if AVs are running
                 |
                 | - DLL inject into explorer.exe
                 |
                 | - Else: extract dll and run using rundll32.exe
                 |
                 | - Set registry keys and delete installer...
+---------+      
| Network | 
+---------+              
           
[EV-Core] --+ 
            |    Use sendMessage and getUpdates for c&c
            |                     | 
            +--------------api.telegram.org-------------Telegram client
```
*Features*
----------
* Will support screenshots, keylogging, password recovery, download and execute, and remote command execution. No webcam capture because thats just plain creepy...
* Will be supported on win XP-10

