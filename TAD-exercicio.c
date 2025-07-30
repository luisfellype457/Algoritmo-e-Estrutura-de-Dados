typedef struct {
    int num;
    int den;
} RACIONAL;

void soma(RACIONAL *a, RACIONAL *b, RACIONAL *c){
    c->num = a->num * b->den + a->den * b->num;
    c->den = a->den * b->den;
}

int equivalencia(RACIONAL *a, RACIONAL *b){
    return (a->num * b->den == a->den * b->num);
}