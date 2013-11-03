// compiles on Mac OS-X with the following cmd line: 
// gcc -o ex1 -std=c99 -I /usr/include/libxml2 ex1.c -lxml2


#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include <libxml/parser.h>

//typedef struct _xmlParserCtxt XmlParserCtx_t;
typedef struct _xmlSAXHandler XmlSaxHandler_t;


// --------------------------------------------------------------------------
// local function  declarations
// --------------------------------------------------------------------------

void saxNotationDecl(void *ctx, xmlChar const* name, const xmlChar *publicId, const xmlChar *systemId);


void saxStartDocument(void *ctx);
void saxEndDocument(void *ctx);
void saxStartElement(void *ctx, xmlChar const* name, xmlChar const* atts[]);
void saxEndElement(void *ctx, xmlChar const* name);
void saxReference(void *ctx, xmlChar const* name);
void saxCharacters(void *ctx, xmlChar const* ch, int len);
void saxIgnorableWhitespace(void *ctx, xmlChar const* ch, int len);
void saxProcessingInstruction(void *ctx, xmlChar const* target, xmlChar const* data);
void saxComment(void *ctx, xmlChar const* value);
void saxCdataBlock(void *ctx, xmlChar const* value, int len);
void saxWarning(void* ctx, const char* msg, ...);
void saxError(void* ctx, const char* msg, ...);
void saxFatalError(void* ctx, const char* msg, ...);


// --------------------------------------------------------------------------
// --------------------------------------------------------------------------
int main(int argc, char** argv)
{
   int rc = 0;
   xmlInitParser();
   xmlParserCtxtPtr ctx = xmlNewParserCtxt();
   if ( !ctx ) goto exit;
   xmlInitParserCtxt(ctx);

   XmlSaxHandler_t saxHandler;
   memset(&saxHandler,0, sizeof saxHandler);
   saxHandler.startDocument = saxStartDocument;
   saxHandler.endDocument = saxEndDocument;
   saxHandler.startElement = saxStartElement;
   saxHandler.endElement = saxEndElement;
   saxHandler.reference = saxReference;
   saxHandler.characters = saxCharacters;
   saxHandler.ignorableWhitespace = saxIgnorableWhitespace;
   saxHandler.processingInstruction = saxProcessingInstruction;
   saxHandler.comment = saxComment;
   saxHandler.cdataBlock = saxCdataBlock;
   saxHandler.warning = saxWarning;
   saxHandler.error = saxError;
   saxHandler.fatalError = saxFatalError;

   rc = xmlSAXUserParseFile(&saxHandler, ctx, "ex1.xml");

   printf ("xmlSAXUserParseFile() returned: %d\n", rc );
   
exit:
   if ( ctx ) xmlFreeParserCtxt(ctx);
   xmlCleanupParser();
   return 0;
}


// --------------------------------------------------------------------------
// local function definitions
// --------------------------------------------------------------------------
void saxStartDocument(void *ctx)
{
   printf("start document\n");
}

// --------------------------------------------------------------------------
void saxEndDocument(void *ctx)
{
   printf("end document\n");
}

// --------------------------------------------------------------------------
void saxStartElement(void *ctx, xmlChar const* name, xmlChar const* *atts)
{
   printf("start element '%s'\n", name);
   if ( atts ) {
      printf("attributes: \n");
      for (int i=0; atts[i]!=0 && atts[1+i]!=0; i+=2 )  {
	 printf("\t[%d] '%s' : '%s'\n", i, atts[i], atts[i+1]);
      }
   }
}



// --------------------------------------------------------------------------
void saxEndElement(void *ctx, xmlChar const* name)
{
   printf("end element'%s'\n", name);
}

// --------------------------------------------------------------------------
void saxReference(void *ctx, xmlChar const* name)
{
   printf("reference: '%s'\n", name);
}

// --------------------------------------------------------------------------
void saxCharacters(void *ctx, xmlChar const* ch, int len)
{
   const xmlChar* p = ch; 
   while ( p < (ch + len) ){
      if ( *p != ' ' && *p != '\t'  && *p != '\n' ) break;
      ++p;
   }
   if ( len && (p < (ch + len)) ) {
   printf("%d characters:\n", len);
   char* s = malloc(len+1);
   if ( s ) {
      memset(s, 0, len+1);
      memcpy(s, ch, len); 
      printf("'%s'\n", s);
      free(s);
   }
   }
}

// --------------------------------------------------------------------------
void saxIgnorableWhitespace(void *ctx, xmlChar const* ch, int len)
{
   printf("%d characters of ignorable whitespace\n", len);
}

// --------------------------------------------------------------------------
void saxProcessingInstruction(void *ctx, xmlChar const* target, xmlChar const* data)
{
   printf("PI: '%s' '%s'\n", target, data);
}

// --------------------------------------------------------------------------
void saxComment(void *ctx, xmlChar const* value)
{
   printf("comment: %s\n", value);
}

// --------------------------------------------------------------------------
void saxCdataBlock(void *ctx, xmlChar const* ch, int len)
{
   const xmlChar* p = ch;
   while ( p < (ch + len) ){
      if ( *p != ' ' && *p != '\t'  && *p != '\n' ) break;
      ++p;
   }
   if ( len && (p < (ch + len)) ) {
   printf("%d CDataBlock:\n", len);
   char* s = malloc(len+1);
   if ( s ) {
      memset(s, 0, len+1);
      memcpy(s, ch, len); 
      printf("'%s'\n", s);
      free(s);
   }
   }
}



// --------------------------------------------------------------------------
void saxWarning(void* ctx, const char* msg, ...)
{
}


// --------------------------------------------------------------------------
void saxError(void* ctx, const char* msg, ...)
{
}


// --------------------------------------------------------------------------
void saxFatalError(void* ctx, const char* msg, ...)
{
}




