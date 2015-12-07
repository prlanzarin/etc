(* ************************************************
 *
 * PROFESSOR: ÁLVARO MOREIRA
 * DISCIPLINA: SEMÂNTICA FORMAL N - 2015/2
 * TRABALHO 3: GERADOR DE CONDIÇÕES DE VERIFICAÇÃO
 * ALUNO: PAULO RENATO LANZARIN
 * CARTÃO: 228818
 *
 * ************************************************)

type status = Progr | Logical

type aexp = 
    Var of string * status
    | Num of int
    | Sum of aexp * aexp
    | Mult of aexp * aexp
    | Min of aexp * aexp
    | Fat of aexp

type bexp =
    PBool of bool
    | POr of bexp * bexp
    | PAnd of bexp * bexp
    | PNot of bexp 
    | PEq of aexp * aexp
    | PLeq of aexp * aexp
    | PUneq of aexp * aexp

type astn = 
    ABool of bool
    | AOr of astn * astn
    | AAnd of astn * astn
    | ANot of astn
    | AImpl of astn * astn
    | AEq of aexp * aexp
    | ALeq of aexp * aexp
    | AUneq of aexp * aexp

type cmd = 
    Skip
    | Asg of string * aexp
    | Seq of cmd * cmd
    | If of bexp * cmd * cmd
    | Wh of bexp * astn * cmd (* annotated while *)
   
let rec aexpTostr (a:aexp) = match a with
    Var(x, _) -> x
    | Num(n) -> string_of_int n
    | Sum(a1, a2) -> "(" ^ (aexpTostr a1) ^ " + " ^ (aexpTostr a2) ^ ")"
    | Mult(a1, a2) -> "(" ^ (aexpTostr a1) ^ " * " ^ (aexpTostr a2) ^ ")"
    | Min(a1, a2) -> "(" ^ (aexpTostr a1) ^ "   " ^ (aexpTostr a2) ^ ")"
    | Fat(a1) -> "(" ^ (aexpTostr a1) ^ "!)"

let rec astnTostr (a:astn) = match a with
    ABool (true) -> "T"
    | ABool (false) -> "F"
    | AOr (f, g) -> "(" ^ (astnTostr f) ^ " or " ^ (astnTostr g) ^ ")"
    | AAnd (f, g) -> "(" ^ (astnTostr f) ^ " and " ^ (astnTostr g) ^ ")"
    | ANot f -> "(not " ^ (astnTostr f) ^ ")"
    | AImpl (f, g) -> "(" ^ (astnTostr f) ^ " ==> " ^ (astnTostr g) ^ ")"
    | AEq(a1, a2) -> "(" ^ (aexpTostr a1) ^ " == " ^ (aexpTostr a2) ^ ")"
    | ALeq(a1, a2) -> "(" ^ (aexpTostr a1) ^ " <= " ^ (aexpTostr a2) ^ ")"
    | AUneq(a1, a2) -> "(" ^ (aexpTostr a1) ^ " <> " ^ (aexpTostr a2) ^ ")"

(* Converts IMP's boolean expressions abstract syntax trees to
 * logic assertion language formulas *)
let rec bexpToastn = function
    | PBool(t) -> ABool(t)
    | POr(t1, t2) -> (AOr(bexpToastn(t1), bexpToastn(t2)))
    | PAnd(t1, t2) -> (AAnd(bexpToastn(t1), bexpToastn(t2)))
    | PNot(t) -> ANot(bexpToastn(t))
    | PEq(t1, t2) -> AEq(t1, t2)
    | PLeq(t1, t2) -> ALeq(t1, t2)
    | PUneq(t1, t2) -> AUneq(t1, t2)

(* Substituition on arithmetic expressions *)
let rec asubst x (a:aexp) = function
    | Var(y, s) -> if ((x = y) && (s = Progr)) then a else Var (y, s)
    | Num(n) -> Num n
    | Sum(a1, a2) -> Sum (asubst x a a1, asubst x a a2)
    | Mult(a1, a2) -> Mult (asubst x a a1, asubst x a a2)
    | Min(a1, a2) -> Min (asubst x a a1, asubst x a a2)
    | Fat(a1) -> Fat(asubst x a a1)

(* Substituition on assertions *)
let rec subst x (a:aexp) = function
    | ABool(b) -> ABool(b)
    | AOr(t1, t2) -> AOr(subst x a t1, subst x a t2)
    | AAnd(t1, t2) -> AAnd (subst x a t1, subst x a t2)
    | ANot(t) -> ANot(subst x a t)
    | AImpl(t1, t2) -> AImpl(subst x a t1, subst x a t2)
    | AEq(t1, t2) -> AEq(asubst x a t1, asubst x a t2)
    | ALeq(t1, t2) -> ALeq(asubst x a t1, asubst x a t2)
    | AUneq(t1, t2) -> AUneq(asubst x a t1, asubst x a t2)

(* WPC generator function *)
let rec wpc (c, psi) = match c with 
    Skip -> psi
    | Asg(s, ae) -> subst s ae psi
    | Seq(c1, c2) -> wpc (c1, (wpc(c2, psi)))
    | If(be, c1, c2) -> AAnd(AImpl(bexpToastn be, (wpc(c1, psi))), 
                                AImpl((ANot (bexpToastn be)), wpc(c2, psi)))
    | Wh(be, inv, c) -> inv

(* auxiliary vcg function *)
let rec vcg (c, psi) = match c with
    | Skip -> ABool (true)
    | Asg(s, ae) -> ABool (true)
    | Seq(c1, c2) -> AAnd (vcg(c1, (wpc(c2, psi))), vcg(c2, psi))
    | If(be, c1, c2) -> AAnd(vcg(c1, psi), vcg(c2,psi))
    | Wh(be, inv, c) -> AAnd(
                            AAnd(vcg(c,inv), AImpl(AAnd(inv, (bexpToastn be)),
                                                    wpc(c,inv))),
                            AImpl(AAnd(inv, ANot (bexpToastn be)), psi)) 

(* vcgen (astn * cmd * astn) -> astn *)
let vcgen (psi, c, phi) = 
    print_string (astnTostr (AAnd(AImpl(psi, (wpc(c,phi))), vcg(c,phi))));
    print_string "\n\n" ;;

(* fat function as defined in the specification *)
let fat =
    Seq(Seq(Asg("y", Num 1), Asg("z" , Num 0)) ,
        Wh(PUneq(Var("z", Progr) , Var("x", Progr)),
            AEq(Var("y" , Progr) , Fat(Var("z", Progr))),
            Seq (Asg("z", Sum(Var("z", Progr), Num 1)),
                Asg ("y", Mult(Var("y", Progr), Var("z", Progr))))));;

(* fat2 function as defined in the exercises list *)
let fat2 = 
    Seq(Asg("y", Num 1),
        Wh(PUneq(Var("x", Progr), Num 0),
            AEq(Var("y", Progr), Fat(Var("z", Progr))),
            Seq(Asg("y", Mult(Var("y", Progr), Var("x", Progr))),
                Asg("x", Sum(Var("x", Progr), Num (-1))))));;


(* vcgen for fat app as defined in the specification *)
print_string "VCGEN DE {x >= 0} fat {y = x!}\n";;

vcgen(ALeq (Num 0, Var("x" , Progr)),
        fat,
        AEq(Var("y", Progr), Fat(Var("x", Progr))));; 

(* vcgen for fat with pre-condition {T} and post-condition {y = x!}
 * as defined in the exercises list *)
print_string "VCGEN DE {T} fat {y = x!}\n";;

vcgen(ABool(true),
        fat,
        AEq(Var("y", Progr), Fat(Var("x", Progr))));; 


(* vcgen for fat2 with pre-condition{x = x0 ^ x >= 0} and post-condition {y = x0!}
 * as defined in the exercises list *)
print_string "VCGEN DE {x = x0 and x >= 0} fat2 {y = x!}\n";;

vcgen(AAnd(AEq(Var("x0", Progr), Var("x", Progr)), ALeq(Num 0, Var("x", Progr))),
        fat2,
        AEq(Var("y", Progr), Fat(Var("x0", Progr))));; 


(* SUCC *)

let succ = 
    Seq(Asg("a", (Sum(Var("x", Progr), Num 1))),
        If((PEq(Sum(Var("a", Progr), Num (-1)), Num 0)), 
            (Asg("y", Num 1)),
            (Asg("y", Var("a", Progr)))));;

(* vcgen for succ with pre-condition {T} and post-condition {y = x + 1}
 * as defined in the exercises list *)

print_string "VCGEN DE {T} succ {y = x + 1}\n";;
vcgen(ABool(true),
        succ,
        (AEq(Var("y", Progr), Sum(Var("x", Progr), Num 1))));;


(* EX2 MIN *)
let p =
    If((PEq(Var("y", Progr), Var("x", Progr))),
        (Asg("z", Var("y", Progr))),
        (Asg("z", Var("x", Progr))));;


(* vcgen for p with pre-condition {T} and post-condition {Min(x, y)}
 * as defined in the exercises list *)

print_string "VCGEN DE {T} p {z = Min(x, y)}\n";;

vcgen(ABool(true),
        p,
        AEq(Var("z", Progr), Min(Var("x", Progr), Var("y", Progr))));;

(* EX COPY1, INV = y+a = x *)
let copy1 = 
    Seq((Seq(Asg("a", Var("x", Progr)),
                 Asg("y", Num 0))),
            Wh(PUneq(Var("a", Progr), Num 0),
                AEq(Var("x", Progr), Sum(Var("y", Progr), Var("a", Progr))),
                Seq(Asg("y", Sum(Var("y", Progr), Num 1)),
                        Asg("a", Sum(Var("a", Progr), Num (-1))))));;           

(* vcgen for copy1 with pre-condition {x >= 0} and post-condition {x = y}
 * as defined in the exercises list *)

print_string "VCGEN DE {x >= 0} copy1 {x = y}\n";;
vcgen(ALeq(Num 0, Var("x", Progr)),
        copy1,
        AEq(Var("x", Progr), Var("y", Progr)));;

