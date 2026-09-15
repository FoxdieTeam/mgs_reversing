void rank_800CD178(int *arr, int len)
{
    int i;

    for (i = 0; i < len; i++, arr += 2) {
        arr[0] += arr[1];
    }
}
