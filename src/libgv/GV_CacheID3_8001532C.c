extern int GV_CacheID2_800152FC(const char* fileName, int extID);

//iterates the string to grab the filename up to the period.
//uses the first chracter after the period as the file ext id.
//calls CacheID2 with this information.
int GV_CacheID3_8001532C( char* string )
{
		char filename[32];
		char *pFilename = filename;
		char  pIterator = *string++;

		if ( pIterator == '.' )
		{
			*filename = 0;
		}
		else
		{
LOOP:
				*pFilename++ = pIterator;
				if ( pIterator )
				{
					pIterator = *string++;
					if ( pIterator != '.' )
					{
						goto LOOP;
					}
					*pFilename = 0;
				}
		}
		return GV_CacheID2_800152FC( filename, ( int )*string );
}