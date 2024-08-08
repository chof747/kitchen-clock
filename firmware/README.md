# Kitchen-Clock Firmware

## Setting up development environment

I am developing this library in close connection with the Modfirmware libraries. Therefore I splitted the way libraries are included into the build between development and production:

1. For productive builds, the libraries are taken from specific tags of the respective Git Repositories to ensure a secure state 
2. For development I decided to include the libraries by
   a. cloning the repositories of the modfirmware libraries to a different directory on my machine and then linking these pathes into the lib/ directory of the project

Following this strategy it is possible to work on both: the firmware and the libraries seemlessly. So if you want to also develop on the firmware for the development environment please clone all the git repositories mentioned under ` `[env:prod]` to a place on your local machine and link them into the lib directory.

**TODO:** As soon as the libraries are more developed I will publish them on the PlatformIO Registry so that the cloning and linking to `lib/` will not be necessary anymore.