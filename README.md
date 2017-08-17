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
* Will support screenshots, keylogging, password recovery, download and execute, and remote command execution. No webcam capture because that's just plain creepy...
* Will be supported on win XP-10
* Currently supports download and exec (ALL DNEXEC[url:=path]), remote command execution (ALL EXECUTE[cmd]), and get sysinfo... 
* Https traffic using winhttp...
* Removed base64... Meh

*Command Structure*
-----------
[TO] [TYPE][ARG1(:=ARG2(if present))] 

* Ex: ALL SYSINFO(NO ARGS REQUIRED) 

![alt text](https://raw.githubusercontent.com/JebSmith/EsotericVisage/master/images/data1.PNG)

![alt text](https://raw.githubusercontent.com/JebSmith/EsotericVisage/master/images/data2.PNG)
