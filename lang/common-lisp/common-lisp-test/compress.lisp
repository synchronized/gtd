
(defun compress (lst)
  (if (consp lst)
      (compress-compr (car lst) 1 (cdr lst))
      lst))

(defun compress-compr (elt n lst)
  (if (null lst)
      (list (compress-list-n elt n))
      (let ((next (car lst)))
        (if (eql elt next)
            (compress-compr elt (+ n 1) (cdr lst))
            (cons (compress-list-n elt n) (compress-compr next 1 (cdr lst)))))))

(defun compress-list-n (elt n)
  (if (> n 1)
      (list n elt)
      elt))

(defun uncompress (lst)
  (if (null lst)
      nil
      (let ((elt (car lst))
            (rest (uncompress (cdr lst))))
        (if (consp elt)
            (append (apply #'uncompress-list-n elt) rest)
            (cons elt rest)))))

(defun uncompress-list-n (n elt)
  (if (zerop n)
      nil
      (cons elt (uncompress-list-n (- n 1) elt))))
