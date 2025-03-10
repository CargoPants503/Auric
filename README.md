> [!NOTE]
> AURIC is not affiliated with KYBER for Star Wars Battlefrot II (2017). However AURIC's source code is based on KYBER. For information on KYBER please visit [their website](https://uplink.kyber.gg/news/features-overview/).

<h1 align="center"><img src="https://kyber.gg/logo2.svg" width="30rem"> AURIC</h1>

<h4 align="center">Auric is an Open-Source Private Server tool for STAR WARS™ Battlefront™ (2015).
</h4>
<br>
<p align="center">
  <a href="https://discord.gg/auric">
      <img src="https://img.shields.io/discord/305338604316655616.svg?label=Discord&logo=discord&color=778cd4">
  </a>
  
</p>

------

Auric does not yet have proxy support. The current version relies on Port Forwarding. To make a server joinable, you'll need to open a port through 25200 on your router and share your personal IP (be careful!).




What's done:
* Server starting
* Networking
* NAT Punch-Through system
* Player kicking/moderation
* Per-player team swapping

What isn't done:
* Direct proxy support
* In-Game server browser
* Optimal proxy detection
* UX/UI Styling (WIP)
* Player banning (WIP)
* Database handling at the proxy level

**Stars and PRs are welcome!**

## Credits

* CargoPants - Responsible for the rewrite to port to 2015 Battlefront & Server Mods
* BattleDash - Original Source Code and help debugging
* Andersson799 - Server Crash Fix for MP Inclusion Options, SetTeamId Offset
* Kape1223 - UI/Art, Testing
* Lucapook - Future videos, Testing
* Any/All contributors to Kyber's source code

Auric utilizes the following open-source projects:

- [MinHook](https://github.com/TsudaKageyu/minhook)
- [ImGUI](https://github.com/ocornut/imgui)
- [GLFW](https://glfw.org)
- [cpp-httplib](https://github.com/yhirose/cpp-httplib)
- [openssl](https://openssl.org)
- [executors](https://github.com/chriskohlhoff/executors)
- [nlohmann-json](https://github.com/nlohmann/json)
