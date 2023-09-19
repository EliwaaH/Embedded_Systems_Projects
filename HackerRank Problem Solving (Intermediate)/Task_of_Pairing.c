///////////////////////////////////////////////////////////////////////////////////
// Task Of Pairing
long taskOfPairing(int freq_size, long* freq)
{
    long pairsCnt = 0;

    long prevRemainder = 0;

    for (int i = 0; i < freq_size; i++)
    {
        if (freq[i] == 0)
        {
            prevRemainder = 0;
            continue;
        }

        freq[i] += prevRemainder;
        pairsCnt += freq[i] / 2;
        prevRemainder = freq[i] % 2;
    }

    return pairsCnt;
}