#ifndef UIBASE_STB_IMAGE_H
#define UIBASE_STB_IMAGE_H

extern "C"
{

    extern unsigned char *stbi_load_from_memory(unsigned char const *buffer, 
        int len, int *x, int *y, int *comp, int req_comp) ;

    extern void stbi_image_free(void *retval_from_stbi_load) ;
} ;

#endif//UIBASE_STB_IMAGE_H