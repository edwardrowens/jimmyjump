#include "stdafx.h"
#include "CppUnitTest.h"
#include "PacketService.h"
#include <cstdint>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace TestNetworking {
	TEST_CLASS(TestPacketService) {
public:
	TEST_METHOD(TestExtractInput) {
		std::vector<uint32_t> packedInput{ 1, 3, 67, 2, 1, 9, 1, 0, 10, 0 };

		std::unique_ptr<std::map<uint32_t, std::vector<uint8_t>>> unpackedInput = PacketService::extractInput(packedInput);

		Assert::AreEqual(size_t(3), (*unpackedInput).size());
		Assert::AreEqual((*unpackedInput)[1][0], uint8_t(67));
		Assert::AreEqual((*unpackedInput)[1][1], uint8_t(2));
		Assert::AreEqual((*unpackedInput)[1][2], uint8_t(1));
		Assert::AreEqual((*unpackedInput)[9][0], uint8_t(0));
		Assert::AreEqual(size_t(0), (*unpackedInput)[10].size());
	}


	TEST_METHOD(TestPackInput) {
		// Given
		std::map<uint32_t, std::vector<uint8_t>> keyPressesByFrame;
		keyPressesByFrame[123] = std::vector<uint8_t>{0, 2, 6, 4};
		keyPressesByFrame[0] = std::vector<uint8_t>{0};
		keyPressesByFrame[99999] = std::vector<uint8_t>();

		// When
		std::unique_ptr<std::vector<uint32_t>> packedInput = PacketService::packInput(keyPressesByFrame);

		// Then
		Assert::AreEqual(size_t(11), (*packedInput).size());
		Assert::AreEqual(uint32_t(0), (*packedInput)[0]);
		Assert::AreEqual(uint32_t(1), (*packedInput)[1]);
		Assert::AreEqual(uint32_t(0), (*packedInput)[2]);
		Assert::AreEqual(uint32_t(123), (*packedInput)[3]);
		Assert::AreEqual(uint32_t(4), (*packedInput)[4]);
		Assert::AreEqual(uint32_t(0), (*packedInput)[5]);
		Assert::AreEqual(uint32_t(2), (*packedInput)[6]);
		Assert::AreEqual(uint32_t(6), (*packedInput)[7]);
		Assert::AreEqual(uint32_t(4), (*packedInput)[8]);
		Assert::AreEqual(uint32_t(99999), (*packedInput)[9]);
		Assert::AreEqual(uint32_t(0), (*packedInput)[10]);
	}
	};
}