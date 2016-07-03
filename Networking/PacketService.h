#pragma once

#include <map>
#include <vector>
#include <cstdint>
#include <memory>

namespace PacketService {
	/*
	Inputs the frame at the first index, the number of inputs at the second, and the inputs themselves at every other index.
	*/
	std::unique_ptr<std::vector<uint32_t>> packInput(const std::map<uint32_t, std::vector<uint8_t>>& keyPressByFrame);

	/*
	Extracts the keys pressed by frame which were in the structure set by the PacketService::packInput function
	*/
	std::unique_ptr<std::map<uint32_t, std::vector<uint8_t>>> extractInput(const std::vector<uint32_t>& packedKeyPresses);
}