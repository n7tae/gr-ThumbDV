gr-ThumbDV
===========
## Information

This will build a gnuradion OOT (out-of-tree) module to encode and decode an audio stream using different vocoders available on an AMBE-3000 chip.

It uses the Northwest Digital Radio ThumbDV(tm) AMBE-3000 dongle (http://www.nwdigitalradio.com) to encode and decode between audio and encoded data using either the DStar or DMR vocoder (many other vocoders are available on the AMBE-3000 chip and could be easily added to this OOT). The encoder builds an ecoded data stream from an 8000 sample/second, 16-bit integer audio stream. The decoder converts the encoded data stream back to a 8000 sample/second, 16-bit integer audio stream. 160 16-bit voice sample produce 9 bytes of encoded data and vis-versa.

Be sure to look in the "examples" folder for flow-graphs that make a 16-bit audio file and then use that file to make (and then decode) an encoded stream file. A "bare-bones" DStar transmitter flow-graph is also included.

The **AMBE Encode** and **AMBE Decode** blocks don't provide *any* other processing. A "bare-bones" DStar transmitter can be constructed with the **MBE Encode** block and a collection of standard gnuradio block. The **DStar Sync** and **DStar Slow Data Sink** blocks are can be used in combination with ABME Decode to build a complete DStar receiver. See the included example flow-graphs.

## Installation

Change to any folder in your home directory and enter following commands in your terminal.
```
git clone https://github.com/ac2ie/gr-ThumbDV.git
cd gr-ThumbDV/ 
mkdir build
cd build/
cmake -DCMAKE_INSTALL_PREFIX=path_to_gnuradio_base ../
make
sudo make install
```
The "path_to_gnuradio_base" can be found with the command:
```
gnuradio-config-info --prefix
```

## Updating

Go to the gr-ThumbDV directory and pull any new stuff with `git pull`. If new files are downloaded, the safest thing to do uninstall, rebuild and reinstall:
```
cd build
sudo make uninstall
cd ..
rm -r build
```
and then complete the rebuild at the `mkdir build` command from the "Installation" section.

## Uninstall

If you don't want the ThumbDV blocks anymore, go back to the build directory and...
```
sudo make uninstall
```
After removal, you can go to the parent directory of gr-ThumbDV and safely remove the gr-ThumbDV directory.

## Other Stuff

It is my intention to add additional gnuradio blocks to this OOT that will, when properly connected, build fully functional DStar and DMR receivers and transmitters. I welcome comments and complaints, but moslty I welcome push notifications for improvements.

Thanks to the folks at NorthWest Digital Radio (especially for their ambeserver.c). If you find this software useful, it's because of them. If you don't, you can blame me!

## 73

Tom AC2IE - ac2ie(at)arrl(dot)net
