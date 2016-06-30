#include "PacketService.h"

static std::vector<uint32_t>& packInput(const std::map<uint32_t, std::vector<uint8_t>>& keyPressByFrame) {
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

	return *keyPresses;
}


static std::map<uint32_t, std::vector<uint8_t>>& extractInput(std::vector<uint32_t>&) {

}