(defun search (x w &optional (n 1))
  (cond ((null w) nil)
        ((equal (car w) x) (cons n (search x (cdr w) (+ n 1))))
        (t (search x (cdr w) (+ n 1)))))
 
(print (search 'a '(8 3 a 6 a 1)))

(defun odd_sum (ls)
    (if ls
        (+ (car ls) (odd_sum(cddr ls)))
        '0
    )
)

(princ (odd_sum '(1 3 1 5 1 5 1 1 1)))


(defun inf-to-pref(l)
    (eval(cond 
        ((null l) nil)
        ((atom l) l)
        (t (list (cadr l) (inf-to-pref (car l))  (inf-to-pref (caddr l))))
    ))
)

(princ(inf-to-pref '((2 + 6) / (2 + 2))))
