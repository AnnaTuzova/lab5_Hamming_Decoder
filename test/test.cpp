#include "../Decoder_lib/Decoder.h"
#include <windows.h>
#include <gtest/gtest.h>

TEST(TestHamming74Decoder, ExceptionTest)
{
	std::vector<uint8_t> wrong_input_data{ 0, 1, 0, 2, 4, 0, 1 };
	std::vector<uint8_t> wrong_size_input_data{ 0, 1 };
	Hamming74Decoder hamming_decode;

	ASSERT_THROW(hamming_decode.Decode(wrong_input_data), const char*);
	ASSERT_THROW(hamming_decode.Decode(wrong_size_input_data), const char*);
}


TEST(TestHamming74Decoder, DecodeTest)
{
	std::vector<uint8_t> input_data{ 0,0,0,0,0,0,0,
									 0,0,0,1,1,0,1,
									 0,0,1,0,1,1,1,
									 0,0,1,1,0,1,0,
									 0,1,0,0,0,1,1,
									 0,1,0,1,1,1,0,
									 0,1,1,0,1,0,0,
									 0,1,1,1,0,0,1,
									 1,0,0,0,1,1,0,
									 1,0,0,1,0,1,1,
								 	 1,0,1,0,0,0,1,
									 1,0,1,1,1,0,0,
									 1,1,0,0,1,0,1,
									 1,1,0,1,0,0,0,
									 1,1,1,0,0,1,0,
									 1,1,1,1,1,1,1 };

	std::vector<uint8_t> expected_output_data{ 0,0,0,0,
											   0,0,0,1,
											   0,0,1,0,
											   0,0,1,1,
											   0,1,0,0,
											   0,1,0,1,
											   0,1,1,0,
											   0,1,1,1,
											   1,0,0,0,
											   1,0,0,1,
										  	   1,0,1,0,
											   1,0,1,1,
											   1,1,0,0,
											   1,1,0,1,
											   1,1,1,0,
											   1,1,1,1 };

	Hamming74Decoder hamming_decode;
	std::vector<uint8_t> actual_output_data = hamming_decode.Decode(input_data);
	ASSERT_EQ(actual_output_data, expected_output_data);
}

TEST(TestHamming74Decoder, DecodeWithOneErrorTest)
{
	std::vector<uint8_t> input_data{  1,1,0,1,0,0,0,
									  0,1,0,1,0,0,0,
									  1,0,0,1,0,0,0,
									  1,1,1,1,0,0,0,
									  1,1,0,0,0,0,0,
									  1,1,0,1,1,0,0,
									  1,1,0,1,0,1,0,
									  1,1,0,1,0,0,1 };

	std::vector<uint8_t> expected_output_data{ 1,1,0,1,
											   1,1,0,1,
									           1,1,0,1,
									           1,1,0,1,
									           1,1,0,1,
									           1,1,0,1,
									           1,1,0,1,
									           1,1,0,1 };

	Hamming74Decoder hamming_decode;
	std::vector<uint8_t> actual_output_data = hamming_decode.Decode(input_data);
	ASSERT_EQ(actual_output_data, expected_output_data);
}


TEST(TestHamming74Decoder, DecodeWithTwoErrorTest)
{
	std::vector<uint8_t> input_data_with_two_errors{ 1,1,0,1,0,0,1 };

	std::vector<uint8_t> expected_output_data{ 1,1,0,1 };

	Hamming74Decoder hamming_decode;
	std::vector<uint8_t> actual_output_data = hamming_decode.Decode(input_data_with_two_errors);

	for (int i = 0; i < actual_output_data.size(); i++)
	{
		if (actual_output_data.at(i) == expected_output_data.at(i))
			continue;
		else
			SUCCEED();
	}
	
}

TEST(TestHamming74Decoder, EmptyInputTest)
{
	std::vector<uint8_t> input_data;

	Hamming74Decoder hamming_decode;
	std::vector<uint8_t> actual_data = hamming_decode.Decode(input_data);

	ASSERT_TRUE(actual_data.size() == 0);
}

int main(int argc, char *argv[])
{
	::testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
	return 0;
}
