// CÓDIGO SOBRE TIPO ABSTRATO DE DADO (TAD)

typedef struct{
    int num;
    int den;
}RACIONAL;

void criar_racional(int n, int d, RACIONAL *r){
    r->num = n;
    r->den = d;
}

void multiplicar_racionais(RACIONAL *a, RACIONAL *b, RACIONAL *c){
    c->num = a->num * b->num;
    c->den = a->den * b->den;
}

void somar_racionais(RACIONAL *a, RACIONAL *b, RACIONAL *c){
    c->num = a->num * b->den + a->den * b->num;
    c->den = a->den * b->den;
}

int verif_eqvl(RACIONAL *a, RACIONAL *b){
    return a->num * b->den == a->den * b->num;
}

void reduzir_racional(RACIONAL *rac){
    int a, b, q, r, n, d;

    if (rac->num > rac->den){
        a = rac->num;
        b = rac->den;
    } else {
        a = rac->den;
        b = rac->num;
    }

    while (b){
        q = a/b;
        r = a%b;

        a = b;
        b = r;
    }

    rac->num = rac->num/a;
    rac->den = rac->den/a;
}