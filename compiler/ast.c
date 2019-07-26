
#include "header.h"

/* Methods */

AST_Node *AST_Node_create(u8 type) {

    u32 size = 0;

    switch(type) {
        case NODE_EXP:      size = sizeof(AST_Node_Exp); break;
        case NODE_BLOCK:    size = sizeof(AST_Node_Block); break;
        case NODE_IF:       size = sizeof(AST_Node_If); break;
        case NODE_WHILE:    size = sizeof(AST_Node_While); break;
        case NODE_EXPLIST:  size = sizeof(AST_Node_ExpList); break;
        case NODE_PRINT:    size = sizeof(AST_Node_Print); break;
        case NODE_DICTENTRY:size = sizeof(AST_Node_DictEntry); break;
        case NODE_DICT:     size = sizeof(AST_Node_Dict); break;
        case NODE_BREAK:
        case NODE_CONTINUE: size = sizeof(AST_Node); break;
        case NODE_LABELLIST:size = sizeof(AST_Node_LabelList); break;
        case NODE_FUNCTION: size = sizeof(AST_Node_ObjectFunction); break;
        case NODE_IDENTIFIER: size = sizeof(AST_Node_Identifier); break;
        case NODE_RETURN:   size = sizeof(AST_Node_Return); break;
        case NODE_IMPORT:   size = sizeof(AST_Node_Import); break;
        case NODE_CLASS:    size = sizeof(AST_Node_Class); break;
    }

    AST_Node *node = malloc(size);

    assert(node != 0);

    memset(node, 0, size);

    node->n_type = type;
    node->n_next = 0;
    node->lineno = yylineno;

    return node;
}

/* Expression List */

AST_Node *AST_Node_ExpList_create() {

    AST_Node *node = AST_Node_create(NODE_IF);

    return node;
}

void AST_Node_ExpList_append(AST_Node *node, AST_Node *e) {

    AST_Node_ExpList *l = (AST_Node_ExpList*) node;

    if(!l->head) {
        l->head = e;
    } else {
        l->tail->n_next = e;
    }

    l->tail = e;
    l->count++;
}

/* ObjectFunction node */

AST_Node *AST_Node_ObjectFunction_create(char *name, AST_Node *args, AST_Node *block) {

    AST_Node_ObjectFunction *f = (AST_Node_ObjectFunction*) AST_Node_create(NODE_FUNCTION);

    f->name = name;
    f->args = args;
    f->block = block;

    return (AST_Node*) f;
}

/* LabelList node */

AST_Node *AST_Node_LabelList_create() {
    return AST_Node_create(NODE_LABELLIST);
}

void AST_Node_LabelList_append(AST_Node *_list, char *label) {

    AST_Node_LabelList *list = (AST_Node_LabelList*) _list;

    list->labels[list->count++] = label;

}

/* Identifier node */

AST_Node *AST_Node_Identifier_create(char *base_label) {

    AST_Node_Identifier *id = (AST_Node_Identifier*) AST_Node_create(NODE_IDENTIFIER);

    id->base_label = base_label;
    id->elem_count = 0;

    return (AST_Node*) id;
}

void AST_Node_Identifier_append(AST_Node *_id, AST_Node *index, char *attr_name) {

    AST_Node_Identifier *id = (AST_Node_Identifier*) _id;

    if(index) {
        id->elements[id->elem_count].index = index;
    } else {
        id->elements[id->elem_count].attr_name = attr_name;
    }

    id->elements[id->elem_count].is_index = index != 0;

    id->elem_count++;
}

/* Print node */

AST_Node *AST_Node_Print_create(AST_Node *node) {

    AST_Node_ExpList *l = (AST_Node_ExpList*) node;

    AST_Node_Print *print = (AST_Node_Print*) AST_Node_create(NODE_PRINT);

    print->args = l->head;
    print->arg_count = l->count;

    // free the arg list wrapper

    return (AST_Node*) print;
}

/* If node */

AST_Node *AST_Node_If_create(AST_Node *condition, AST_Node *if_block, AST_Node *else_block) {

    AST_Node_If *node = (AST_Node_If*) AST_Node_create(NODE_IF);

    node->condition = condition;
    node->if_block  = if_block;
    node->else_block = else_block;

    return (AST_Node*) node;
}

void AST_Node_If_append_else(AST_Node *node, AST_Node *else_block) {
    AST_Node_If *_if = (AST_Node_If*) node;
    _if->else_block = else_block;
}

/* While node */

AST_Node *AST_Node_While_create(AST_Node *condition, AST_Node *do_block) {

    AST_Node_While *_while = (AST_Node_While*) AST_Node_create(NODE_WHILE);

    _while->condition = condition;
    _while->do_block = do_block;

    return (AST_Node*) _while;
}

/* Return node */

AST_Node *AST_Node_Return_create(AST_Node *value) {

    AST_Node_Return *_return = (AST_Node_Return*) AST_Node_create(NODE_RETURN);

    _return->value = value;

    return (AST_Node*) _return;
}

/* Block node */

AST_Node *AST_Node_Block_create(AST_Node *child) {

    AST_Node_Block *node = (AST_Node_Block*) AST_Node_create(NODE_BLOCK);

    if(child) {
        node->head = child;
        node->tail = child;
        node->count++;
    }

    return (AST_Node*) node;
}

void AST_Node_append(AST_Node *node, AST_Node *node2) {

    assert(node);
    assert(node2);

    assert(node->n_type == NODE_BLOCK);

    AST_Node_Block *block = (AST_Node_Block*) node;

    if(!block->head) {
        block->head = node2;
    } else {
        block->tail->n_next = node2;
    }

    block->tail = node2;

    block->count++;
}

/* Dict node */

AST_Node *AST_Node_Dict_create() {

    return AST_Node_create(NODE_DICT);

}

void AST_Node_Dict_append(AST_Node *_dict, char *label, AST_Node *value) {

    AST_Node_Dict *dict = (AST_Node_Dict*) _dict;

    AST_Node *entry = AST_Node_create(NODE_DICTENTRY);

    ((AST_Node_DictEntry*) entry)->label = label;
    ((AST_Node_DictEntry*) entry)->value = value;

    if(!dict->head) {
        dict->head = entry;
    } else {
        dict->tail->n_next = entry;
    }

    dict->tail = entry;
    dict->count++;

}

/* Expression Node */

AST_Node *AST_Node_operator(u8 type, AST_Node *l_exp, AST_Node *r_exp) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type = type;
    node->l_exp = l_exp;
    node->r_exp = r_exp;

    if(type == EXP_SELECT || type == EXP_SELECT_ATTR) {
      node->flags = EXP_ASSIGNABLE;
    }

    if((l_exp && (l_exp->flags & EXP_CONSTANT)) || !l_exp) {

      // if the first operand is constant, or there is no first operand

      if((r_exp && (r_exp->flags & EXP_CONSTANT)) || !r_exp) {

        node->flags = EXP_CONSTANT;

      }
    }

    return (AST_Node*) node;
}

AST_Node *AST_Node_dict(AST_Node *_node) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type = EXP_DICT;
    node->value_dict = (AST_Node_Dict*) _node;

    return (AST_Node*) node;
}

AST_Node *AST_Node_true() {
    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);
    node->type = EXP_TRUE;
    node->flags = EXP_CONSTANT;
    return (AST_Node*) node;
}

AST_Node *AST_Node_false() {
    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);
    node->type = EXP_FALSE;
    node->flags = EXP_CONSTANT;
    return (AST_Node*) node;
}

AST_Node *AST_Node_string(char *string) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type = EXP_STRING;
    node->value_string = string;

    node->flags = EXP_CONSTANT;

    return (AST_Node*) node;
}

AST_Node *AST_Node_array(AST_Node *l) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type = EXP_ARRAY;
    node->value_array = (AST_Node_ExpList*) l;

    return (AST_Node*) node;
}

AST_Node *AST_Node_i64(i64 value) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type = EXP_I64;
    node->value_i64 = value;
    node->flags = EXP_CONSTANT;

    return (AST_Node*) node;
}

AST_Node *AST_Node_f64(f64 value) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type = EXP_F64;
    node->value_f64 = value;
    node->flags = EXP_CONSTANT;

    return (AST_Node*) node;
}

AST_Node *AST_Node_label(char *label) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type  = EXP_LABEL;
    node->label = label;
    node->flags = EXP_ASSIGNABLE;

    return (AST_Node*) node;
}

AST_Node *AST_Node_lambda(AST_Node *lambda) {

    AST_Node_Exp *node = (AST_Node_Exp*) AST_Node_create(NODE_EXP);

    node->type  = EXP_LAMBDA;
    node->value_lambda = lambda;
    node->flags = EXP_CONSTANT;

    return (AST_Node*) node;
}

/* Node Import */

AST_Node *AST_Node_import_create(char *name, char *as) {

  AST_Node_Import *node = (AST_Node_Import*) AST_Node_create(NODE_IMPORT);

  node->name = name;
  node->as = as;
  node->flags = 0;

  return (AST_Node*) node;
}

/* Node Class */

AST_Node *AST_Node_Class_create(char *name, AST_Node *members) {

  AST_Node_Class *node = (AST_Node_Class*) AST_Node_create(NODE_CLASS);

  node->name = name;
  node->members = members;
  node->flags = 0;

  return (AST_Node*) node;

}
