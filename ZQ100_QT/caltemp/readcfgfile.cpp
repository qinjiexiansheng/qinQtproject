#include <stdlib.h>
#include <stdio.h>
#include <sys/fcntl.h>
#include <string.h>
#include <ctype.h>
#include <unistd.h>

#define FILENAME_SIZE   100
#define MAX_MAP         1024
#define LINE_SIZE       1024
#define MAX_ITEM        400

typedef struct TItem{
        char key[40];
        char value[40];
} TItem;

class TFile{
public:
        TFile( const char *filename ){
                m_num = 0;
                ::memset(m_items, '\0', sizeof(m_items));
                ::strncpy(m_filename, filename, FILENAME_SIZE-1);
                openFile();
                readFile();
                m_index = 0;
        }

        ~TFile(){
                closeFile();
        }

        void setFilename(const char *filename){ ::strncpy(m_filename, filename, FILENAME_SIZE-1); }
        const char *filename(){ return m_filename; }

        int openFile(){
                closeFile();
                m_fd = open(m_filename, O_RDONLY);
                if( m_fd < 0 ) {
                        perror( "++++readcfgfile +++++=open file failed\n" ); 
                        return -1; 
                }
                return 0;
        }

        void closeFile(){
                if( m_fd > 0 ) {
                	::close(m_fd); 
                        m_fd = -1;
                }
                m_num = 0;
                ::memset(m_items, '\0', sizeof(m_items));
        }

        int readFile(){
                FILE *_fp = fdopen(m_fd, "r");
                if( !_fp ) {  
                        return -1;
                }
                char _buf[LINE_SIZE] = {'\0'};
                while( fgets(_buf, LINE_SIZE, _fp) != NULL ) {
                        parseLine( _buf );
                        memset(_buf, '\0', LINE_SIZE);
                }
                return 0;
        }

        char *findValue( const char *key ){
                for( int i=0; i<m_num; i++ ) {
                        if( strcmp(key, m_items[i].key) == 0 ) {
                                return m_items[i].value;
                        }
                }
//                printf ( "I have not found the item. Key:%s\n", key);

                return NULL;
        }

        int findItem( TItem *item )
        {
                if( item == NULL )
                        return -1;
                for( int i=0; i<m_num; i++ ) {
                        if( strcmp(item->key, m_items[i].key) == 0 ) {
                                strcpy( item->value, m_items[i].value );
                                return 0;
                        }
                }
//                printf ( "I have not found the item. Key:%s\n", item->key);

                return -1;
        }

        int getItem( TItem *item )
        {
                if( item == NULL ) {
                        printf ("[%s, %d] %s: get item failed\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
                        return -1;
                }
                strcpy( item->key, m_items[m_index].key );
                strcpy( item->value, m_items[m_index].value );
                return 0;
        }

        int travelItem( TItem *item )
        {
                if( item == NULL ) {
                        printf ("[%s, %d] %s: get item failed\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
                        return -1;
                }
                strcpy( item->key, m_items[m_index].key );
                strcpy( item->value, m_items[m_index].value );
                if( m_index++ == m_num ) {
                        m_index = 0; 
                }
                return m_index;
        }

        void printItem() 
        {
                int i;
                for( i=0; i<m_num; i++ ) {
                        printf ("Key:%s|Value:%s\n", m_items[i].key, m_items[i].value);
                }
        }

protected:
        inline virtual void parseLine( char *line )
        {
                int _len = strlen(line);
                char *_head = line;
                while( isblank(*_head) ) {
                        _head++; 
                }

                char *_tail = line+_len-1;
                while( isblank(*_tail) ) {
                        _tail--; 
                }

                if( (_tail - _head) <= 0 ) {
                        return;
                }

                if( *_head == '#' ) {
                        printf ("[%s, %d] %s: The line is comment.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__); 
                        return;
                }

                char *_p = _head;
                while( *_p != '=' && _p != _tail ) {
                        _p++; 
                }
                if( _p == _tail ) {
                        return;  
                }
                *_p = ' ';

                if( m_num > MAX_ITEM ) {
                        printf ("[%s, %d] %s: The num has overflow.\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
                        return; 
                }
                int _retn;
                if( (_retn = sscanf( _head, "%39s %39s", m_items[m_num].key, m_items[m_num].value)) != 2 ) {
                        printf ("[%s, %d] %s: Read Item failed\n", __FILE__, __LINE__, __PRETTY_FUNCTION__);
                        return; 
                }
                m_num++;
        }

private:
        char  m_filename[FILENAME_SIZE];
        int   m_fd;
        TItem m_items[MAX_ITEM];
        int   m_num;
        int   m_index;
};

