/* One way to write the function strlen() */

unsigend strlen(const char *s)
{
    register int n = 0;

    for(; *s != '\0'; ++s){
        ++n;
    }
    return n;
}