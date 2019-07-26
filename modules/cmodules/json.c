
#include "../../runtime/header.h"

void skip_spaces(char *text, int *i, int *line) {
  while(text[*i] == ' ' || text[*i] == '\t' || text[*i] == '\n') {
    if(text[*i] == '\n')
      (*line)++;
    (*i)++;
  }
}

Object *parse_dict(Context *context, char *text, int *i, int *line);

Object *parse_string(Context *context, char *text, int *i, int *line) {

  (*i)++;

  char buffer[1024];
  int buffer_size = 0;

  char escaped = 0;

  char c;

  while((text[*i] != '"' || escaped) && text[*i] != 0) {

    c = text[*i];

    if(c == '\n') (*line)++;

    if(escaped) {

      switch(text[*i]) {
        case '\\':break;
        case 'r': c = '\r'; break;
        case 'n': c = '\n'; break;
        case 't': c = '\t'; break;
      }

      escaped = 0;

    } else {

      if(c == '\\') {
        escaped = 1;
      }

    }

    assert(buffer_size < 1024);

    buffer[buffer_size] = 0;

    buffer[buffer_size++] = c;
    (*i)++;
  }

  buffer[buffer_size] = 0;

  if(text[*i] == 0) {
    printf("fail 0");
    return 0;

  }

  (*i)++; // skip the "

  return ObjectString_from_cstring(context, buffer);
}

Object *parse_number(Context *context, char *text, int *i, int *line) {

  char buffer[1024];
  int buffer_size = 0;
  char got_dot = 0;

  int sign = 1;

  if(text[*i] == '+') {

    (*i)++;

  } else if(text[*i] == '-') {

    sign = -1;

    (*i)++;
  }

  while(((text[*i] <= '9' && text[*i] >= '0') || (text[*i] == '.' && !got_dot)) && text[*i] != 0) {

    assert(buffer_size < 1024);

    buffer[buffer_size++] = text[*i];

    (*i)++;
  }

  buffer[buffer_size] = 0;

  if(text[*i] == 0) {
    printf("fail 1");
    return 0;
  }

  if(got_dot)
    return ObjectFloat_from_cdouble(context, sign*strtod(buffer, 0));
  return ObjectInt_from_cint(context, sign*strtoll(buffer, 0, 0));

}

Object *parse_array(Context *context, char *text, int *i, int *line) {

  (*i)++;

  Object *array, *temp;

  array = Object_create(context, __ObjectArray__, 0, 0);

  while(1) {

    temp = 0;

    skip_spaces(text, i, line);

    switch(text[*i]) {

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9': temp = parse_number(context, text, i, line); break;
      case '"': temp = parse_string(context, text, i, line); break;
      case '[': temp = parse_array(context, text, i, line);  break;
      case '{': temp = parse_dict(context, text, i, line);   break;
      case ']': (*i)++; return array;
    }

    if(!temp) {
      return 0;
    }

    ObjectArray_append(array, (Object*[]) {temp}, 1);

    skip_spaces(text, i, line);

    if(text[*i] == ']') {

      (*i)++;

      break;

    } else if(text[*i] == ',') {

      (*i)++;

    } else {

      return 0;

    }

  }

  return array;
}

Object *parse_dict(Context *context, char *text, int *i, int *line) {

  (*i)++;

  char key[1024];
  int  key_size;

  Object *temp, *dict;

  dict = Object_create(context, __ObjectDict__, 0, 0);

  while(1) {

    temp = 0;

    skip_spaces(text, i, line);

    if(text[*i] != '"') {

      // invalid json

      return 0;

    } else if(text[*i] == '}') {

      // empty dict

      return dict;

    }

    (*i)++;

    // read the key

    key_size = 0;

    while(text[*i] != '"' && text[*i] != 0) {

      key[key_size] = 0;

      assert(key_size < 1024);

      key[key_size++] = text[*i];

      (*i)++;
    }

    key[key_size] = 0;

    if(text[*i] == 0) { // string ended unexpectedly

      return 0;
    }

    (*i)++; // skip the closing quotes

    skip_spaces(text, i, line);

    if(text[*i] != ':') {

      return 0;
    }

    (*i)++;

    skip_spaces(text, i, line);

    switch(text[*i]) {

      case '0':
      case '1':
      case '2':
      case '3':
      case '4':
      case '5':
      case '6':
      case '7':
      case '8':
      case '9':
      case '-':
      case '+': temp = parse_number(context, text, i, line); break;

      case 'f':
      if(text[(*i) + 1] == 'a' &&
         text[(*i) + 2] == 'l' &&
         text[(*i) + 3] == 's' &&
         text[(*i) + 4] == 'e') {

        temp = NOJA_False;

        (*i) += sizeof("false")-1;

      } else {

        return 0;
      }
      break;
      case 't':
      if(text[(*i) + 1] == 'r' &&
         text[(*i) + 2] == 'u' &&
         text[(*i) + 3] == 'e') {

        temp = NOJA_True;

        (*i) += sizeof("true")-1;

      } else {

        return 0;

      }

      break;
      case 'n':
      if(text[(*i) + 1] == 'u' &&
         text[(*i) + 2] == 'l' &&
         text[(*i) + 3] == 'l') {

        temp = NOJA_False; // not right!

        (*i) += sizeof("null")-1;

      } else {

        return 0;
      }
      break;
      case '{': temp = parse_dict(context, text, i, line);   break;
      case '[': temp = parse_array(context, text, i, line);  break;
      case '"': temp = parse_string(context, text, i, line); break;

    }

    if(!temp)
      return 0;

    Dict_cinsert(dict, key, temp);

    skip_spaces(text, i, line);

    if(text[*i] == '}') {

      (*i)++;

      break;

    } else if(text[*i] == ',') {

      (*i)++;

    } else {

      return 0;
    }


  }

  return dict;
}

Object *JSON_decode(Object *self, Object **argv, u32 argc) {

  char *text = ((ObjectString*) argv[0])->value;

  int i = 0;
  int line = 1;

  skip_spaces(text, &i, &line);

  if(text[i] != '{') {
    printf("invalid syntax at line %d\n", line);
    return NOJA_False;
  }

  Object *result = parse_dict(self->context, text, &i, &line);

  if(!result) {
    printf("invalid syntax at line %d\n", line);
    return NOJA_False;
  }
  return result;

}

Object *JSON_encode(Object *self, Object **argv, u32 argc) {
  return NOJA_False;
}

char Module_json_init(Object *dest) {

  Dict_cinsert(dest, "encode", ObjectCFunction_create(dest->context, &JSON_encode));
  Dict_cinsert(dest, "decode", ObjectCFunction_create(dest->context, &JSON_decode));

  return 1;
}
