Flow-Graph Examples
===========
## 16bit-audio-recorder.grc
Start with this flow-graph to record a 8 kHz, 16-bit audio file. Just specify a name for the file. Then execute the flow-graph and record something. Stop the exection dialog as soon as you are done recording. That will terminate the file. This file can then be used as input for the other flow-graphs in this folder.
## ambe-encode.grc
This flow-graph will encode your recorded audio file and save the result in another file. Point the file source to the recorded file. Be sure to turn off the repeat, otherwise the flow-graph will run until you manually stop the execution dialog. Set the file sink to point to the output file. In the Encode block you can select either the DStar or the DMR vocoder. If you have a newer ThumbDV (tm), you can slect the higher 460800 baudrate.
## ambe-decode.grc
This flow-graph will play your encoded file. Point the file source to the encoded file. Be sure to set the proper dvmode on the Decode block.
## simple-dstar-transmitter.grc
This flow-graph will transmit you recorded audio file. Point the File Source to the audio file you recorded. "DStar" must be selected in the Encode block. The Stream Mux blocks wrap the raw data from the Enocde block into the proper DStar voice-frame format. This transmission data is "bare-bones" and contains no DStar header, slow-data or termination flag. The voice frame data is fed to a GMSK modulator and then transmitted. Of course you have to have a device that supports transmissions. This flow-graph uses a Ettus Research UHD device. If you are using another device, you'll have to replace the rf sink with your own sink. You may have to play with the sample rate (and the samples/symbol in the GMSK modulator) to satisfy the requirements of other transmit-capable devices.
