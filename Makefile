.PHONY:runtest
all:libRoute.a sender receiver timeManager processing
CC=gcc
CFLAGS=-Wall -Werror -Wextra -pedantic -g3
RM = rm -f

libRoute.a: decidePathQuality.o createFile.o stringMatch.o processing_Tokenise.o subStringMatch.o convert2CharToHex.o binaryToInteger.o binaryBitsConversion.o  createSockStructure.o createFrameBuffer.o integerToCharacter.o characterToInteger.o characterToBinary8Bit.o receiver_SubStringMatchSelfMac.o receiver_CheckMacIsPresent.o receiver_PacketIdentification.o receiver_SubStringMatch1.o  sender_TakeActionDependOnFile.o sender_SendNotDeadPacket.o sender_SendBroadcastPacket.o sender_CreateNotDeadFrame.o processing_TakeActionDependOnLine.o  receiver_GetIndexOfMac.o deleteOneLine.o
	ar -cvq libRoute.a decidePathQuality.o subStringMatch.o createFile.o stringMatch.o convert2CharToHex.o binaryToInteger.o binaryBitsConversion.o createSockStructure.o createFrameBuffer.o integerToCharacter.o characterToInteger.o characterToBinary8Bit.o receiver_CheckMacIsPresent.o receiver_PacketIdentification.o receiver_SubStringMatchSelfMac.o receiver_SubStringMatch1.o sender_TakeActionDependOnFile.o sender_SendBroadcastPacket.o sender_SendNotDeadPacket.o sender_CreateNotDeadFrame.o processing_TakeActionDependOnLine.o processing_Tokenise.o receiver_GetIndexOfMac.o deleteOneLine.o
	$(RM) *.o 


deleteOneLine.o: deleteOneLine.c
	 	  $(CC) $(CFLAGS) -c deleteOneLine.c

decidePathQuality.o: decidePathQuality.c
	 	  $(CC) $(CFLAGS) -c decidePathQuality.c

createFile.o: createFile.c
	 	  $(CC) $(CFLAGS) -c createFile.c

subStringMatch.o: subStringMatch.c
	 	  $(CC) $(CFLAGS) -c subStringMatch.c

stringMatch.o: stringMatch.c
	 	  $(CC) $(CFLAGS) -c stringMatch.c

characterToBinary8Bit.o:characterToBinary8Bit.c
		  $(CC) $(CFLAGS) -c characterToBinary8Bit.c

characterToInteger.o:characterToInteger.c
		  $(CC) $(CFLAGS) -c characterToInteger.c

integerToCharacter.o:integerToCharacter.c
		  $(CC) $(CFLAGS) -c integerToCharacter.c

binaryBitsConversion.o:binaryBitsConversion.c 
		  $(CC) $(CFLAGS) -c binaryBitsConversion.c 

binaryToInteger.o:binaryToInteger.c 
		  $(CC) $(CFLAGS) -c binaryToInteger.c 

createFrameBuffer.o: createFrameBuffer.c
	 	  $(CC) $(CFLAGS) -c createFrameBuffer.c

createSockStructure.o: createSockStructure.c
	 	  $(CC) $(CFLAGS) -c createSockStructure.c

convert2CharToHex.o:convert2CharToHex.c
		  $(CC) $(CFLAGS) -c convert2CharToHex.c

processing_Tokenise.o: processing_Tokenise.c
	 	  $(CC) $(CFLAGS) -c processing_Tokenise.c

processing_TakeActionDependOnLine.o: processing_TakeActionDependOnLine.c
	 	  $(CC) $(CFLAGS) -c processing_TakeActionDependOnLine.c

sender_CreateNotDeadFrame.o: sender_CreateNotDeadFrame.c
	 	  $(CC) $(CFLAGS) -c sender_CreateNotDeadFrame.c

sender_SendBroadcastPacket.o: sender_SendBroadcastPacket.c
	 	  $(CC) $(CFLAGS) -c sender_SendBroadcastPacket.c

sender_SendNotDeadPacket.o: sender_SendNotDeadPacket.c
	 	  $(CC) $(CFLAGS) -c sender_SendNotDeadPacket.c

sender_TakeActionDependOnFile.o:sender_TakeActionDependOnFile.c
		  $(CC) $(CFLAGS) -c sender_TakeActionDependOnFile.c

receiver_CheckMacIsPresent.o:receiver_CheckMacIsPresent.c
		  $(CC) $(CFLAGS) -c receiver_CheckMacIsPresent.c

receiver_PacketIdentification.o:receiver_PacketIdentification.c
		  $(CC) $(CFLAGS) -c receiver_PacketIdentification.c

receiver_SubStringMatchSelfMac.o: receiver_SubStringMatchSelfMac.c
	 	  $(CC) $(CFLAGS) -c receiver_SubStringMatchSelfMac.c

receiver_SubStringMatch1.o: receiver_SubStringMatch1.c
	 	  $(CC) $(CFLAGS) -c receiver_SubStringMatch1.c

receiver_GetIndexOfMac.o: receiver_GetIndexOfMac.c
	 	  $(CC) $(CFLAGS) -c receiver_GetIndexOfMac.c

sender:sender.c libRoute.a
	  	  $(CC) $(CFLAGS) -o sender sender.c libRoute.a

receiver:receiver.c libRoute.a
		  $(CC) $(CFLAGS) -o receiver receiver.c libRoute.a

timeManager:timeManager.c libRoute.a
		  $(CC) $(CFLAGS) -o timeManager timeManager.c libRoute.a

processing:processing.c libRoute.a
	  	  $(CC) $(CFLAGS) -o processing processing.c libRoute.a

runS:
		sudo ./sender ReceiverInfo.txt 30 10 10000
	#	sudo valgrind --leak-check=full --leak-resolution=high --num-callers=40 ./sender ReceiverInfo.txt 60 10 100
	#sudo ./sender

runR:
		sudo ./receiver ReceiverInfo.txt TimeInfo.txt 60 3000
	#	sudo valgrind --leak-check=full --leak-resolution=high --num-callers=40 ./receiver ReceiverInfo.txt TimeInfo.txt 60 3000
	#sudo ./receiver
runT:
		sudo ./timeManager TimeInfo.txt 60
	#	sudo valgrind --leak-check=full --leak-resolution=high --num-callers=40 ./timeManager TimeInfo.txt 60

runP:
		sudo ./processing 3000
	#	sudo valgrind --leak-check=full --leak-resolution=high --num-callers=40 ./processing 3000

clean:
	$(RM) sender receiver timeManager processing libRoute.a  *.txt
