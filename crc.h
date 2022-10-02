/**
 * crc32 - Calculate the CRC32 for a block of data
 *
 * @crc: Input crc to chain from a previous calculution (use 0 to start a new
 *	calculation)
 * @buf: Bytes to checksum
 * @len: Number of bytes to checksum
 * Return: checksum value
 */
uint32_t calculate_crc32c(uint32_t crc, const unsigned char *buf, unsigned int len);

/**
 * Compute the CRC-32 of the bootloader control struct.
 *
 * Only the bytes up to the crc32_le field are considered for the CRC-32
 * calculation.
 *
 * @param[in] abc bootloader control block
 *
 * Return: crc32 sum
 */
static uint32_t ab_control_compute_crc(struct bootloader_control *abc)
{
	return calculate_crc32c(0, (void *)abc, offsetof(typeof(*abc), crc32_le));
}
