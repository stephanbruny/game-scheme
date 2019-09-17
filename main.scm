; (define current-time 0)
; (define (render dt)
;     (set! current-time (+ dt current-time))
;     (let (
;         (mx (floor (/ current-time 10)))
;     )
;         (if (> mx 1280.0)
;             (set! current-time 0)
;         )
;         (clear-screen 0 0 0)
;         (set-color mx 255 128)
;         (draw-rect (list (+ 20 mx) 20 220 250))
;         (set-color 128 255 64)
;         (draw-rect (list 300 300 220 250))
;     )
; )
; (game render)
(define (rand-vec2 n m)
    (cons (random n) (random m))
)
(define (rand-move)
    (rand-vec2 2.0 2.0)
)
(define (rand-pos)
    (rand-vec2 256 144)
)
(define (makelist fn n)
  (if (= n 0)
     (list 0)                       ; base case. Just return (0)
     (cons (fn) (makelist fn (- n 1)))))

(define li1 (makelist rand-pos 100))
(define mvs (makelist rand-move 100))
; (display li1)

; (for-each (lambda (item)
;     (if (pair? item)
;         ((display "Pair\n"))
;     )
; ) li1)


(define current-time 0)
(define tx 0.0)
(define tex)
(define rect_1 (rectangle 0 0 16 16))
(define (render-sprites spritelist)
    (for-each (lambda (pos)
        (if (pair? pos)
            (texture->draw tex (car pos) (cdr pos))
        )
    ) spritelist)
)
(define (on-load)
    (set! tex (texture->load "spike-medium.png"))
    (display "Texture: ") 
    (display (texture->width tex))
    (display " : ")
    (display (texture->height tex))
    (display "\n")
)
(define (render)
    (draw-text "Hello from Scheme!" (inexact->exact (+ 10 tx)) 20 20 (color->rgb 255 0 255))
    (texture->draw tex 8 8)
    (render-sprites li1)
)
(define (update dt)
    (set! current-time (+ dt current-time))
    (set! tx (floor (/ current-time 0.025)))
)
(game 800 600 "Tinkerboy with Raylib" on-load update render)
(texture->unload tex)