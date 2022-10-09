(defun poisk (x w &optional (n 1))
  (cond ((null w) nil)
        ((equal (car w) x) (cons n (poisk x (cdr w) (+ n 1))))
        (t (poisk x (cdr w) (+ n 1)))))
 
(print (poisk 'a '(8 3 a 6 a 1)))
