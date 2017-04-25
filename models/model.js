var mongoose = require('mongoose');
var Schema = mongoose.Schema;

var demoSchema = new Schema({
    Name_g : String,
    Name_s : String,
    Difficulty: Number,
    Engagement: Number,
    Review: String,
    createTime: {
        type: Date,
        default: Date.now
    }
});

var FeedbackSchema = new Schema({
    _Major :{
        type : String,
        default : "XXXX"
    },
    _Name :{
        type : String,
        default : "0000"
    },
    _Instuctor:{
        type : String,
        default : "Professor X"
    },
    _Difficulty:{
        type : Number,
        default : 9999
    },
    _Review:{
        type : String,
        default : "Why not change the world?"
    },
    
    // Difficulty: Number,
    // Boringness: Number,
    // Time_Commitment: Number,
    // Review: String,
    createTime: {
        type: Date,
        default: Date.now
    }
});

exports.Demo = mongoose.model('demo', demoSchema, 'demo');
exports.Feedback = mongoose.model('Feedback', FeedbackSchema)
