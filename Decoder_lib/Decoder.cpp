#include "Decoder.h"

std::vector<uint8_t> Hamming74Decoder::Decode(std::vector<uint8_t> &input_data)
{
	if (std::fmod(input_data.size(), kNumOfInputElements) != 0)
		throw "Error: The size of the input data is not divided by 7.";
	CheckInputDataOnCorrect(input_data);

	int output_data_size = ((input_data.size() / 7) * 4);
	std::vector<uint8_t> output_data(output_data_size);

	std::vector<uint8_t> syndrom_vector = SyndromeCalculation(input_data);
	ÑorrectionError(input_data, syndrom_vector);

	int j = 0; //It is necessary that at each iteration of the i-loop the j variable is not reset.
	for (int i = 0; i < input_data.size(); i += kNumOfInputElements)
	{
		for (j; j < output_data.size(); j++)
		{
			output_data.at(j) = input_data.at(i);
			output_data.at(j + 1) = input_data.at(i + 1);
			output_data.at(j + 2) = input_data.at(i + 2);
			output_data.at(j + 3) = input_data.at(i + 3);

			j += kNumOfOutputElements;
			break;
		}
	}

	return output_data;
}

void Hamming74Decoder::CheckInputDataOnCorrect(std::vector<uint8_t> &input_data)
{
	for (int i = 0; i < input_data.size(); i++)
	{
		if (input_data.at(i) == 0 || input_data.at(i) == 1)
			continue;
		else
			throw "Error: invalid input data.";
	}
}

std::vector<uint8_t> Hamming74Decoder::SyndromeCalculation(std::vector<uint8_t> &input_data)
{
	int syndrom_size = ((input_data.size() / 7) * 3);
	std::vector<uint8_t> syndrom_vector(syndrom_size);

	int j = 0;
	for (int i = 0; i < input_data.size(); i += kNumOfInputElements)
	{
		for (j; j < syndrom_vector.size(); j++)
		{
			syndrom_vector.at(j) = input_data.at(i) ^ input_data.at(i + 2) ^ input_data.at(i + 3) ^ input_data.at(i + 4);
			syndrom_vector.at(j + 1) = input_data.at(i) ^ input_data.at(i + 1) ^ input_data.at(i + 2) ^ input_data.at(i + 5);
			syndrom_vector.at(j + 2) = input_data.at(i + 1) ^ input_data.at(i + 2) ^ input_data.at(i + 3) ^ input_data.at(i + 6);
			j += kNumOfSyndromElements;
			break;
		}
	}

	return syndrom_vector;
}

void Hamming74Decoder::ÑorrectionError(std::vector<uint8_t> &input_data, std::vector<uint8_t> &syndrom_vector)
{
	int j = 0;
	for (int i = 0; i < input_data.size(); i += kNumOfInputElements)
	{
		for (j; j < syndrom_vector.size(); j++)
		{
			if (syndrom_vector.at(j) == 0 && syndrom_vector.at(j + 1) == 0 && syndrom_vector.at(j + 2) == 0)
			{
				j += kNumOfSyndromElements;
				break;
			}

			else if (syndrom_vector.at(j) == 1 && syndrom_vector.at(j + 1) == 1 && syndrom_vector.at(j + 2) == 0)
				input_data.at(i) = std::abs(input_data.at(i) - 1);

			else if (syndrom_vector.at(j) == 0 && syndrom_vector.at(j + 1) == 1 && syndrom_vector.at(j + 2) == 1)
				input_data.at(i + 1) = std::abs(input_data.at(i + 1) - 1);

			else if (syndrom_vector.at(j) == 1 && syndrom_vector.at(j + 1) == 1 && syndrom_vector.at(j + 2) == 1)
				input_data.at(i + 2) = std::abs(input_data.at(i + 2) - 1);

			else if (syndrom_vector.at(j) == 1 && syndrom_vector.at(j + 1) == 0 && syndrom_vector.at(j + 2) == 1)
				input_data.at(i + 3) = std::abs(input_data.at(i + 3) - 1);

			else if (syndrom_vector.at(j) == 1 && syndrom_vector.at(j + 1) == 0 && syndrom_vector.at(j + 2) == 0)
				input_data.at(i + 4) = std::abs(input_data.at(i + 4) - 1);

			else if (syndrom_vector.at(j) == 0 && syndrom_vector.at(j + 1) == 1 && syndrom_vector.at(j + 2) == 0)
				input_data.at(i + 5) = std::abs(input_data.at(i + 5) - 1);

			else if (syndrom_vector.at(j) == 0 && syndrom_vector.at(j + 1) == 0 && syndrom_vector.at(j + 2) == 1)
				input_data.at(i + 6) = std::abs(input_data.at(i + 6) - 1);
	
			j += kNumOfSyndromElements;
			break;
		}
	}
}