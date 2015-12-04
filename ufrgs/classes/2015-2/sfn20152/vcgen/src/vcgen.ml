type status = Progr | Logical

type aexp = 
    Var of string * status
    | Num of int
    | Sum of aexp * aexp
    | Mult of aexp * aexp
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

type cmd  
    Skip
    | Asg of string * aexp
    | Seq of cmd * cmf
    | If of bexp * cmd * cmd
    | Wh of bexp * astn * cmd (* annotated while *)
    
let rec aexpTostr (a:aexp) = match a with
    Var(x, _) -> x
    | Num(n) -> string_of_int n
    | Sum(a1, a2) -> "(" ^ (aexpTostr a1) ^ " + " ^ (aexpTostr a2) ^ ")"
    | Mult(a1, a2) -> "(" ^ (aexpTostr a1) ^ " x " ^ (aexpTostr a2) ^ ")"
    | Min(a1, a2) -> "(" ^ (aexpTostr a1) ^ "   " ^ (aexpTostr a2) ^ ")"
    | Fat(a1) -> "(" ^ (aexpToStr a1) ^ "!)"

let rec astnTostr (a:astn) = match a with
    ABool (true) → ”T”
    | ABool (false) → ”F”
    | AOr (f, g) → ”(” ˆ (astnTostr f) ˆ ” or ” ˆ (astnTostr g) ˆ ”)”
    | AAnd (f, g) → ”(” ˆ (astnTostr f) ˆ ” and ” ˆ (asntTostr g) ˆ ”)”
    | ANot f → ”(not ” ˆ (astnTostr f) ˆ ”)”
    | AImpl (f, g) → ”(” ˆ (astnTostr f) ˆ ” ==> ” ˆ (astnTostr g) ˆ ”)”
    | AEq(a1, a2) → ”(” ˆ (aexpTostr a1) ˆ ” == ” ˆ (aexpTostr a2) ˆ ”)”
    | ALeq (a1, a2) → ”(” ˆ (aexpTostr a1) ˆ ” <= ” ˆ (aexpTostr a2) ˆ ”)”
    | AUneq (a1, a2) → ”(” ˆ (aexpTostr a1) ˆ ” <> ” ˆ (aexpTostr a2) ˆ ”)”

(* Converts IMP's boolean expressions abstract syntax trees to
 * logic assertion language formulas *)
let rec bexpToastn = function
    | PBool(t) -> ABool(t)
    | POr(t1, t2) -> (AOr(bexpToastn(t1), bexpToastn(t2)))
    | PAnd(t1, t2) -> (AAnd(bexpToastn(t1), bexpToastn(t2)))
    | PNot(t) -> -> ANot(bexpToastn(t))
    | PEq(t1, t2) -> AEq(t1, t2)
    | PLeq(t1, t2) -> ALeq(t1, t2)
    | PUneq(t1, t2) -> AUneq(t1, t2)

(* Substituition on arithmetic expressions *)
let rec asubst (a:aexp) = function
    | Var (y, s) -> if ((x = y) && (s = Progr)) then a else Var (y, s)
    | Num(n) -> Num n
    | Sum(a1, a2) -> Sum (asubst x a a1, asubst x a a2)
    | Mult(a1, a2) -> Mult (asubst x a a1, asubst x a a2)
    | Min(a1, a2) -> Min (asubst x a a1, asubst x a a2)
    | Fat(a1) -> Fat(asubst x a a1)

(* Substituition on assertions *)
let rec subst x (a:exp) = function
    | ABool(b) -> ABool(b)
    | AOr(t1, t2) -> AOr(subst x a t1, subst x a t2)
    | AAnd(t1, t2) -> AAnd (subst x a t1, subst x a t2)
    | ANot(t) -> ANot(subst x a t)
    | AImpl(t1, t2) -> AImpl(subst x a t1, subst x a t2)
    | AEq(t1, t2) -> AEq(asubst x a t1, asubst x a t2)
    | ALeq(t1, t2) -> ALeq(asubst x a t1, asubst x a t2)
    | AUneq(t1, t2) -> AUneq(asubst x a t1, asubst x a t2)
