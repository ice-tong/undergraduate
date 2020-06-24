(defun my-length (L) (cond ((null L) 0)
	(T (+ 1 (my-length (cdr L))))))

(defun my-memq (A L)
	(cond ((null L) nil)
		((eq A (car L)) L)
		(T (my-memq A (cdr L)))))

(defun my-append (L1 L2)
	(cond ((null L1) L2)
		((null (cdr L1)) (cons (car L1) L2))
		(T (cons (car L1) (my-append (cdr L1) L2)))))

(defun my-attach (o L)
	(cond ((null L) (list o))
		(T (cons (car L) (my-attach o (cdr L))))))


(defun my-assoc (A L)
	(cond ((null L) nil)
		((eq (car (car L)) A) (car L))
		(T (my-assoc A (cdr L)))))

(defun freq (A L)
	(cond ((null L) 0)
		((and (atom (car L)) (eq A (car L))) (+ 1 (freq A (cdr L))))
		((and (atom (car L)) (not (eq A (car L))) (freq A (cdr L))))
		(T (+ (freq A (car L)) (freq A (cdr L))))))

(defun mapping (L val)
	(cond ((null L) nil)
		((<= (car (car L)) val) (cons (car (cdr (car L))) (mapping (cdr L) val)))
		(T (mapping (cdr L) val))))

(defun my-last (A L)
	(cond ((null L) nil)
		((null (my-memq A (cdr L))) (my-memq A L))
		(T (my-last A (cdr L)))))

(defun my-reverse (L)
	(cond ((null (cdr L)) L)
		(T (my-append (my-reverse (cdr L)) (cons (car L) nil)))))

(defun is-pattern? (pat str)
	(cond ((null str) nil)
		((null pat) nil)
		((is-substring? pat (my-memq (car pat) str)) (my-memq (car pat) str))
		(T (is-pattern? pat (cdr str)))))

(defun is-substring? (pat str)
	(cond ((null pat) T)
		((not (eq (car pat) (car str))) nil)
		(T (and T (is-substring? (cdr pat) (cdr str))))))

(defun first-atom (L)
	(cond ((null L) nil)
		((atom (car L)) (car L))
		(T (first-atom (car L)))))

(defun find-all (A L)
	(cond ((null L) nil)
		((eq (car (my-flatten L)) A) (my-reverse (my-attach (car (cdr (my-flatten L))) (find-all A (cdr L)))))
		(T (find-all A (cdr (my-flatten L))))))

(defun my-flatten (L)
	(cond ((null L) nil)
		((atom L) (list L))
		((listp L) (my-append (my-flatten (car L)) (my-flatten (cdr L))))))
