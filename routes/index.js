var express = require('express');
var router = express.Router();

var mongoose = require('mongoose');
const fetch = require('node-fetch');
var model = require('../models/model');
var Demo = model.Demo;
var Feedback = model.Feedback;

mongoose.connect('mongodb://localhost/borilliant_feedback');

// router.get('/', function(req, res, next) {
//     Demo.find(function(err, docs) {
//         res.render('index', {
//             title: 'Main',
//             demos: docs
//         });
//     });
// });

router.get('/', function(req, res, next) {
    Demo.find().distinct('Name_g', function(error, subjects) {
        res.render('index', {
            title: 'Main',
            demos: subjects
        });
    });
});

router.get('/trip', function(req, res, next) {
    fetch(`http://api.tripadvisor.com/api/partner/2.0/map/42.729164,-73.678503/attractions?key=fab17784-d8ff-4094-ab3f-e0f81a8df0a5`)
    .then(response => response.json())
    .then(body => res.send(body.data))
});


router.get('/index_2.html', function(req, res, next) {
    var Name_g = req.query.Name_g;
    var docs = [];

    if (Name_g && Name_g != '') {
        Demo.find().distinct('Name_s', function(error, subjects) {
            console.log("SUB:" + subjects);
            subjects.forEach(function(element) {
                Demo.findOne({Name_s: element}, function(error, moreElement) {
                    if(moreElement.Name_g === Name_g) {
                        console.log(element);
                        docs.push(moreElement);
                    }
                })

            })
            console.log(docs);
            setTimeout(function () {
                res.render('index_2', {
                    title: 'Choose the sepcific course you want',
                    demos: docs
                });
            },1000)
        });

        }
});


router.get('/add.html', function(req, res, next) {
    Demo.find(function(err, docs) {
        res.render('add', {
            title: 'Add New Review',
            demos: docs
        });
    });
});

router.post('/add.html', function(req, res, next) {

    var demo = new Demo({
        Name_g: req.body.Name_g.replace(/\s/g, '-'),
        Name_s: req.body.Name_s.replace(/\s/g, '-'),
        Difficulty: req.body.Difficulty,
        Engagement: req.body.Engagement,
        Review: req.body.Review
    });

    console.log('======================create========================');

    demo.save(function(err, doc) {
        console.log(doc);
        res.redirect('/');
    });

});

router.get('/del.html', function(req, res, next) {

    var id = req.query.id;

    if (id && id != '') {
        console.log('=====================delete id = ' + id);
        Demo.findByIdAndRemove(id, function(err, docs) {
            console.log(docs);
            res.redirect('/');
        });
    }

});

router.get('/update.html', function(req, res, next) {

    var Name_s = req.query.Name_s;

    if (Name_s && Name_s != '') {
        Demo.find({'Name_s' : Name_s}, function(err, docs) {
            res.render('update', {
                title: 'Course Details',
                demos: docs
            });
        });

    }

});

// New Route

router.get('/create_feedback', (req, res, next) => {
    console.log("TEST PAGE GET LOADED");
    res.send("WELCOME TO TEST PAGE");
});

//////// CREATE
router.post('/create_feedback', (req, res) => {
    console.log('======ADDING NEW COUSE========');
    // let {Major, Name, Instuctor, Difficulty,
        //  Boringness, Time_Commitment, Review} = req.body;
    let {Major, Name, Instuctor, Difficulty, Review } = req.body;
    // console.log(Major);
    // console.log('======successfully get the data from the req========');
    let newFeedback = new Feedback();
    newFeedback._Major = Major;
    newFeedback._Name = Name;
    // newFeedback._Instuctor = Instuctor;
    // newFeedback.Difficulty = Difficulty;
    // newFeedback._Review = Review;

    console.log('======successfully created the original object========');


    newFeedback.save((err) => {
        if(err) console.log(err);
        else{
            console.log("successfully registered");
            res.send ("success ... ");
        }
    });


});


//////// READ
router.get('/read_feedback_all', (req, res, next) => {
    Feedback.find( (err, all_feedbacks) => {
        if(err) res.send(err);
        else{
            console.log(all_feedbacks);
            res.send(all_feedbacks);
        }
    });
});

router.get('/get_major_list',(req, res, next) =>{
    Feedback.find().distinct('_Major', (err, major_list)=>{
        if(err) res.send(err);
        else{
            console.log(major_list);
            res.send(major_list);
        }
    });
});


//////// UPDAE
// find the target feed back first with GET 
router.get('/update_a_feedback', (req, res, next)=>{
    let {id} = req.body;
    Feedback.findById(id, (err, target_feedback)=>{
        if(err) res.send(err);
        else{
            res.send(target_feedback);
        }
    });
});

// use POST req to update it 
router.post('/update_a_feedback', (req, res, next)=>{
    let {id, Major, Name} = req.body;
    Feedback.findById(id, (err, target_feedback)=>{
        if(err) res.send(err);
        else{
            target_feedback._Major = Major;
            target_feedback._Name = Name;
            res.send(target_feedback);
        }
    });

});



//////// DELETE
router.post('/delete_a_feedback', (req, res)=>{
    let {id} = req.body;
    Feedback.findByIdAndRemove(id, (err, target_feedback)=>{
        if(err) res.sned(err);
        else{
            res.send(target_feedback);
        }
    });
});

// test for angular
router.get('/ng', (req, res, next) => {
  res.render('index_angular.html', { title: 'TEST PAGE' });
});
router.get('/test', (req, res, next) => {
  res.render('test.html', { title: 'TEST PAGE' });
});
module.exports = router;
