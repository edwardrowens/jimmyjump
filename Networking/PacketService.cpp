#include "PacketService.h"

std::unique_ptr<std::vector<uint32_t>> PacketService::packInput(const std::map<uint32_t, std::vector<uint8_t>>& keyPressByFrame) {
	std::map<uint32_t, std::vector<uint8_t>>::const_iterator iter = keyPressByFrame.begin();
	std::unique_ptr<std::vector<uint32_t>> keyPresses(new std::vector<uint32_t>);

	for (iter; iter != keyPressByFrame.end(); ++iter) {
		// input the frame
		(*keyPresses).push_back(iter->first);
		// input the amount of keys pressed
		(*keyPresses).push_back(iter->second.size());
		// input the keys pressed
		for (auto i : iter->second)
			(*keyPresses).push_back(i);
	}

	return keyPresses;
}


std::unique_ptr<std::map<uint32_t, std::vector<uint8_t>>> PacketService::extractInput(const std::vector<uint32_t>& packedKeyPresses) {
	std::unique_ptr<std::map<uint32_t, std::vector<uint8_t>>> keyPressesByFrame(new std::map<uint32_t, std::vector<uint8_t>>);
	std::vector<uint32_t>::const_iterator packedKeyPressesIter = packedKeyPresses.begin();

	while (packedKeyPressesIter != packedKeyPresses.end()) {
		// store the frame and allocate the vector of key presses
		uint32_t frame = *packedKeyPressesIter;
		std::vector<uint8_t> keyPresses(*(++packedKeyPressesIter));
		uint8_t numberOfInputs = *packedKeyPressesIter++;

		// collect all the key presses
		for (int i = 0; i < numberOfInputs; ++i) {
			keyPresses[i] = (*packedKeyPressesIter);
			++packedKeyPressesIter;
		}

		// add the key presses to the map
		(*keyPressesByFrame)[frame] = keyPresses;
	}

	return keyPressesByFrame;
}