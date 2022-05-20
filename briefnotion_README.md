# About the Fork

RTLSDR-Airband needs an API. 

My first thought was to have a direct application to application interface 
between two programs.  Sadly, I couldn't find any information regarding a 
communication, via shared variables, to accomplish the ability to check 
status of another program or exchange control properties. 

I will approach creating an api via the amateuar layman's file monitoring 
process.  

First step will be to add simple controls, such as shut down, and read 
open or active frequencies from RASFled.  

The last forseeable step will be to be able to monitor and change all 
significant parameters, such as frequency, scan type, squelch, bandwith, 
audio filter and denoiser (not sure its even part of the program yet), 
modulation type, and whatever else required for me to change and catch 
audio on some other channel, without the need to open a config file or 
dropping to a bash and start entering things when sitting in some parking 
lot in the middle of nowhere. 