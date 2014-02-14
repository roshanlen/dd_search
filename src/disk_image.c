#define MAX_KEYWORD_LEN 64
struct header
{
        unsigned int offset;
        unsigned int last; 
        char         keyword[MAX_KEYWORD_LEN];
        void*        payload;
        unsigned int payload_size;
};


void save_page(int fd, struct header* header, unsigned int* payload_ofst)
{
        int wr_count; 
        off_t ofst;

        header->offset = *payload_ofst;
        wr_count=write(fd,header,sizeof(struct header)); 

        if (wr_count != sizeof(struct header))
                return;
        /* save the current file position */
        ofst=lseek(fd,0,SEEK_CUR);
        lseek(fd,*payload_ofst,SEEK_SET);
        
        /* save the contents */
        wr_count=write(fd,header->payload,header->payload_size); 

        /* restore the file position */
        lseek(fd,ofst,SEEK_SET);
}


