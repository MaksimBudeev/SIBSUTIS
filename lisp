(defun search (x w &optional (n 1))
  (cond ((null w) nil)
        ((equal (car w) x) (cons n (search x (cdr w) (+ n 1))))
        (t (search x (cdr w) (+ n 1)))))

(defun odd_sum (ls)
    (if ls
        (+ (car ls) (odd_sum(cddr ls)))
        '0
    )
)

(defun inf-to-pref(l)
    (eval(cond 
        ((null l) nil)
        ((atom l) l)
        (t (list (cadr l) (inf-to-pref (car l))  (inf-to-pref (caddr l))))
    ))
)

(print (odd_sum '(1 3 1 5 1 5 1 1 1)))
(print (inf-to-pref '((-8 + 10) * (12 / 3))))
(print (search 'a '(3 3 a 2 a 12)))
