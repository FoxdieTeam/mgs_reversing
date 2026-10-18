// vrsave: VR revision copy of libgcl/variable.c
// (crc32), no named twin: the VR save manager carries its own copy; adapted from the asm
unsigned int vrsave_800C5E90( int len, unsigned char *ptr )
{
    unsigned int crc;
    int          counter;

    crc = 0xffffffff;
    if ( len != 0 )
    {
        do
        {
            crc ^= *ptr++;
            counter = 8;

            do
            {
                if ( ( crc & 1 ) != 0 )
                {
                    crc = crc >> 1 ^ 0xedb88320;
                }
                else
                {
                    crc = crc >> 1;
                }
            } while ( --counter != 0 );
        } while ( --len != 0 );
    }
    return ~crc;
}
