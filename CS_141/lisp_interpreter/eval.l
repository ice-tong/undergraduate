;; my-assoc returns the association (binding) of a variable in the association
;; list.  An alist is a list of this form:
;; ((var1 . val1) (var2 . val2) ... (varN . valN))
;; where each vari is a symbol representing a variable (or parameter) name
;; and each vali is the value of the variable.
;; assoc returns the association of a given symbol, e.g,
;; (assoc 'myvar '((a . 10)(b a b c)(myvar d e f)))
;; returns (myvar d e f) and you take the cdr of that to get myvar's value
;; (d e f)
;; We will use alists for the stack of variables and their values.  Assoc
;; always finds the first association of a variable, and this is how we
;; implement dynamic scoping.  New defintions of a variable will hide older
;; definitions, but the older definitions will come back into scope when
;; recursive evaluation unwinds.
;; setq and defun will push a new association on the global-alist.
;; whenever we apply a function, we will bind the formals to the evaluated
;; actuals pushing these new bindings onto the local alist and then
;; evaluate the body of the function in that new scoping context.

(defun my-assoc (v alist)
	(cond ((null alist) nil)
		((eq v (caar alist)) (car alist))
		(T (my-assoc v (cdr alist)))
	)
)

(defun my-eval (e alist)
    (cond ((atom e) (my-eval-atom e alist))
          (t (my-apply (car e) (cdr e) alist))
    )
)

(defun my-eval-atom (e alist)
    (cond ((eq T e) T)
	((eq nil e) nil)
	((numberp e) e)
	((stringp e) e)
	(T (cdr (my-assoc e alist)))
    )
)

(defun my-apply (fn args alist)
    (cond ((atom fn) (my-apply-atom fn args alist))
          (t (my-apply-lambda fn args alist)))
)

(defun my-eval-list (l alist)
    (my-eval (car l) alist)
    (cond ((null l) nil)
	((null (cdr l)) (my-eval (car l) alist))
	(T (my-eval-list (cdr l) alist))
    )
)

(defun my-apply-lambda (fn args alist)
;; bind the formals to the evaluated actuals then evaluate the body in that
;; new scoping context (i.e., that becomes the new alist for recursive
;; evaluation of the function body.  Return the value of the last 
;; expression in the body (using eval-list).
    (my-eval-list (cdr fn) (my-bind-formals (car fn) args alist))
)

(defun my-bind-formals (formals actuals alist)
;; This takes a list of formals and unevaluated actuals.  It should evaluate
;; each actual and bind it to its corresponding formal placing them all on
;; the front of the alist.  It should return the alist with the new bindings
;; on the front.  This will be used to evaluate calls to functions defined
;; via defun.
;; e.g., (my-bind-formals '(a) '((add 1 b)) '((b . 10)))
;; will return ((a . 11) (b . 10))
;; Note there will be one actual parameter for each formal parameter.
    (cond ((null formals) alist)
	(T (cons (cons (car formals) (my-eval (car actuals) alist)) (my-bind-formals (cdr formals) (cdr actuals) alist)))
    )
)

;; Handle the primitives as special cases, then
;; handle user defined functions (defined via defun) in the default case.
;; These are the only functions we handle: eq, car, cdr, cons, quote, cond,
;; defun, eval, setq, and user defined functions (defined via defun) that
;; we have evaluated.  You can add more built-ins (like plus, times, atom,
;; listp) as you like for testing.
(defun my-apply-atom (fn args alist)
    (cond ((eq fn 'eq) (eq (my-eval (car args) alist) (my-eval (cadr args) alist))
	  )
          ((eq fn 'car) (car (my-eval (car args) alist))
          )
          ((eq fn 'cdr) (cdr (my-eval (car args) alist))
          )
          ((eq fn 'cons) (cons (my-eval (car args) alist) (my-eval (cadr args) alist))
          )
          ((eq fn 'quote) (car args) 
          )
	  ((eq fn '+) (+ (my-eval (car args) alist) (my-eval (cadr args) alist))
	  )
	  ((eq fn 'null) (null (my-eval (car args) alist))
	  )
          ((eq fn 'setq) (my-eval-setq (car args) (cadr args)))
          ((eq fn 'cond) (my-eval-cond args alist))
          ((eq fn 'defun) (my-eval-defun args alist))
          ((eq fn 'eval) (my-eval (my-eval (car args) alist) alist))
          (T (my-apply (cdr (my-assoc fn alist)) args alist))
    )
)


(defun my-eval-setq (var val)
    (cdar (setq global-alist (cons (cons var (my-eval val global-alist)) global-alist)))
)

(defun my-eval-cond (clauses alist)
    (cond ((eq T (my-eval (caar clauses) alist)) (my-eval (cadar clauses) alist))
	(T (my-eval-cond (cdr clauses) alist))
    )
)

(defun my-eval-defun (body alist)
;; just push the function body onto the global alist.  It is already an
;; association, e.g., (equal (L1 L2) (cond (...))) and (assoc 'equal in
;; the global alist will return this.  You can then take the cdr and you
;; have a list containing the formal parameters and the expressions in
;; the function body.
    (caar (setq global-alist (cons body global-alist)))
)

(setq global-alist nil)
;; to push a new value, (setq global-alist (cons (cons 'newvar 'newval) global-alist))

(defun my-top ()
    (prog ()
        top (print (my-eval (read) global-alist))
            (terpri) ;; prints a newline
            (go top) ;; loops forever
    )
)
