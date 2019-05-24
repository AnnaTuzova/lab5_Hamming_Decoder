#pragma once 

#include <iostream>
#include <vector>
#include <cstdint>

class IDecode
{
public:
	~IDecode() {}

	virtual std::vector<uint8_t> Decode(std::vector<uint8_t> &input_data) = 0;
};

class Hamming74Decoder : public IDecode
{
private:
	const int kNumOfInputElements = 7;
	const int kNumOfOutputElements = 4;
	const int kNumOfSyndromElements = 3;

	bool CheckInputDataOnCorrect(const std::vector<uint8_t> &input_data) const;
	std::vector<uint8_t> SyndromeCalculation(const std::vector<uint8_t> &input_data) const;
	void ÑorrectionError(std::vector<uint8_t> &input_data, const std::vector<uint8_t> &syndrom_vector);

public:
	~Hamming74Decoder() {}

	std::vector<uint8_t> Decode(std::vector<uint8_t> &input_data) override;
};