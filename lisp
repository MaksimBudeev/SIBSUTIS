22222222222222222222222222222222222222222222222222222222222222
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




333333333333333333333333333333333333333333333333333333333333333

(defun f (a b)
    (if a
        (if (member(car a) b)
            T
            (f (cdr a) b)
        )
        nil
    )
)

(print (f '(1 2 3 4) '(7 8 0 )))

(defun f (matrix)
    (if matr
        (cons
            (caar matrix)
            (f (cdr matrix))
        )
    )
)

(defun g (matrix)
    (if (car matrix)
        (cons
            (cdar matrix)
            (g(cdr matrix))
        )
    )
)

(defun h (matrix)
    (if (car matrix)
        (cons (f matrix) (h (g matrix)))
    )
)

(print (h '((1 2 3 4) (5 6 7 8) (9 10 11 12))))

(defun f (ld lst1 lst2)
    (if (and lst1 lst2)
    (cons
        (funcall ld (car lst1) (car lst2))
        (f ld (cdr lst1) (cdr lst2))
    )
    )
)

(princ(f (lambda (x y) (* x y)) '(10 12 3) '(7 1 4)))

(print(f (lambda (x y) (if (< x y) x y)) '(2 3 4) '(1 5 6)))
